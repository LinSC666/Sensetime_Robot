#include "ros/ros.h"
#include <nmea_msgs/Sentence.h>
#include "mapper.cpp"
#include <serial/serial.h>
#include <geometry_msgs/PoseStamped.h>
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/Quaternion.h"
#include "sensor_msgs/NavSatFix.h"
#include <cmath>
#include <thread>
#include <atomic>
#include <mutex>
#include "../include/httplib.h"
#include "../include/json.hpp"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class RtkGpsNode {
public:
    RtkGpsNode() :
            node_("~"),
            sentence_subscriber_(node_.subscribe("/nmea_sentence", 10, &RtkGpsNode::sentenceCallback, this)),
            gps_NED_publisher_(node_.advertise<geometry_msgs::PoseStamped>("/gps_ned", 1000)),
            gps_GGA_publisher_(node_.advertise<sensor_msgs::NavSatFix>("/gps_gga", 1000)),
            gps_odom_publisher_(node_.advertise<geometry_msgs::PoseStamped>("/gps_odom", 1000)),
            stop_thread_flag_(false) {
        startRateCheckThread();
        gps_odom_data_.header.frame_id = "/odom";
    }

    ~RtkGpsNode() {
        stop_thread_flag_ = true;
        rate_check_thread_.join();
    }

    void sentenceCallback(const nmea_msgs::Sentence::ConstPtr &msg) {
        ros::Time current_time = ros::Time::now();
        if (sentences_package_.empty()) {
            package_timestamp_ = current_time;
        }
        const double kOneSecond = 1e9;
        if (current_time - package_timestamp_ >= ros::Duration(0, 0) &&
            current_time - package_timestamp_ < ros::Duration(0, 0.5 * kOneSecond) &&
            !findSentencesBeginMark(msg->sentence)) {
            sentences_package_.push_back(msg->sentence);
        } else {
            sendAndProcessSentence();
            package_timestamp_ = current_time;
            vector<std::string>().swap(sentences_package_);
            sentences_package_.push_back(msg->sentence);
        }
    }

    void openSerial(const std::string &port = "/dev/ttyUSB0") {
        while (ros::ok()) {
            ROS_INFO("Trying to open serial ...");
            try {
                serial_.setPort(port);
                serial_.setBaudrate(115200);
                serial::Timeout to = serial::Timeout::simpleTimeout(1000);
                serial_.setTimeout(to);
                serial_.open();
                break;
            }
            catch (serial::IOException &e) {
                ROS_ERROR_STREAM("Unable to open Serial Port " + port + "!");
            }
        }
    }

    void readSerialSentence() {
        if (serial_.available()) {
            std::string str_receive = serial_.read(serial_.available());
            sendAndProcessSentence();
        }
    }

    void writeCommand(const char *command,
                      const double &lat = 23.226,
                      const double &lon = 113.456,
                      const double &alt = 95.0) {
        if (serial_.available()) {
            ROS_INFO_STREAM("Sending serial...\n");
            if (!strcmp(command, "disable")) {
                ROS_INFO("Write disable command ...");
                generateDisableCommand();
            } else if (!strcmp(command, "coordinate")) {
                ROS_INFO("Write base coordinate command ...");
                generateDisableCommand();
                generateSerialCommand(lat, lon, alt);
            } else if (!strcmp(command, "surver")) {
                ROS_INFO("Write surver in command ...");
                generateSurverInCommand();
            } else if (!strcmp(command, "frequency")) {
                ROS_INFO("Write frequency changed command ...");
                generateFrequencyCommand();
            }
        }
    }

private:
    static void findElementInSentence(const std::string &s,
                                      std::vector<std::string> &v) {
        std::string::size_type pos1, pos2;
        pos2 = s.find(',');
        pos1 = 0;
        while (std::string::npos != pos2) {
            v.push_back(s.substr(pos1, pos2 - pos1));
            pos1 = pos2 + 1;
            pos2 = s.find(',', pos1);
        }
        if (pos1 != s.length())
            v.push_back(s.substr(pos1));
    }

    static bool findSentencesBeginMark(const std::string &str) {
        return str.find("$GNTXT,BASE") != std::string::npos;
    }

    void sendAndProcessSentence() {
        ros::Time current_time = ros::Time::now();
        sensor_msgs::NavSatFix gps_wgs_data;
        geometry_msgs::PoseStamped gps_ned_data;

        gps_wgs_data.header.stamp = current_time;
        gps_ned_data.header.stamp = current_time;
        gps_odom_data_.header.stamp = current_time;
        for (const auto &str_receive : sentences_package_) {
            processWGS(str_receive, gps_wgs_data, gps_ned_data, gps_odom_data_);
        }
        // obtainHeadingFromPhone("10.9.98.175", gps_odom_data_);
        gps_odom_publisher_.publish(gps_odom_data_);
        gps_GGA_publisher_.publish(gps_wgs_data);
        gps_NED_publisher_.publish(gps_ned_data);
    }

    static void transferStrToOrientation(const std::string &s,
                                         geometry_msgs::PoseStamped &gps_ned_data) {
        std::vector<std::string> v;
        findElementInSentence(s, v);
        if (v.max_size() >= 6 && !v[4].empty()) {
            gps_ned_data.pose.orientation = tf::createQuaternionMsgFromYaw(
                    tfRadians(90 - std::strtod(v[4].c_str(), nullptr)));
        }
    }

    static void transferStrToWGS84(const std::string &s,
                                   sensor_msgs::NavSatFix &gps_gga_data) {
        std::vector<std::string> v;
        findElementInSentence(s, v);
        if (v.max_size() >= 6 &&
            (v[6] == "1" || v[6] == "2" || v[6] == "3" || v[6] == "4" || v[6] == "5" || v[6] == "6" || v[6] == "7" ||
             v[6] == "8" || v[6] == "9")) {
            double lat = 0, lon = 0;

            if (!v[2].empty())
                lat = std::strtod(v[2].c_str(), nullptr) / 100;
            int ilat = (int) floor(lat) % 100;
            lat = ilat + (lat - ilat) * 100 / 60;

            if (!v[4].empty())
                lon = std::strtod(v[4].c_str(), nullptr) / 100;
            int ilon = (int) floor(lon) % 1000;
            lon = ilon + (lon - ilon) * 100 / 60;

            gps_gga_data.latitude = lat;
            gps_gga_data.longitude = lon;
            gps_gga_data.status.status = std::strtod(v[6].c_str(), nullptr);
        }
        if (v[2].empty() || v[4].empty())
            ROS_ERROR("Error received GNGGA sentence!");
    }

    static void transferStrToPosition(const std::string &s,
                                      geometry_msgs::PoseStamped &gps_txt_data) {
        std::vector<std::string> v;
        findElementInSentence(s, v);
        if (v.max_size() >= 6 && (v[3] == "4" || v[3] == "5")) {
            if (v[3] == "5")
                ROS_WARN("GPS state doesn't fix!");
            double angle = std::strtod(v[4].c_str(), nullptr);
            std::string::size_type pos1, pos2;
            pos1 = 0;
            pos2 = v[5].find('*');
            double length = std::strtod(v[5].substr(pos1, pos2 - pos1 + 1).c_str(), nullptr);
            double x = length * sin(angle / 180. * M_PI);
            double y = length * cos(angle / 180. * M_PI);
            if (x < -100 || x > 100 || y < -100 || y > 100)
                ROS_WARN("Position out of range!");
            gps_txt_data.pose.position.x = x;
            gps_txt_data.pose.position.y = y;
        } else {
            ROS_ERROR("Error received GNTXT BASE sentence!");
        }
    }

    void processWGS(const std::string &str_receive,
                    sensor_msgs::NavSatFix &gps_gga_data,
                    geometry_msgs::PoseStamped &gps_ned_data,
                    geometry_msgs::PoseStamped &gps_odom_data) {
        if (str_receive.find("$GNGGA") != std::string::npos) {
            const std::string &available_str = str_receive;
            transferStrToWGS84(available_str, gps_gga_data);
        }

        if (str_receive.find("$GNTXT,BASE") != std::string::npos) {
            const std::string &available_str = str_receive;
            transferStrToPosition(str_receive, gps_odom_data);
            {
                std::lock_guard<std::mutex> lock(last_available_time_mutex_);
                last_txt_base_available_time_ = ros::Time::now();
            }
        }

        if (str_receive.find("$GNTXT,ROVER") != std::string::npos) {
            const std::string &available_str = str_receive;
            transferStrToOrientation(available_str, gps_odom_data);
            {
                std::lock_guard<std::mutex> lock(last_available_time_mutex_);
                last_txt_rover_available_time_ = ros::Time::now();
            }
        }
    }

    static void obtainHeadingFromPhone(const std::string &phone_ip,
                                       geometry_msgs::PoseStamped &gps_ned_data) {
        httplib::Client cli(phone_ip.c_str(), 8080);

        auto res = cli.Get("/sensors.json");
        if (res && res->status == 200) {
            nlohmann::json json_obj = nlohmann::json::parse(res->body);
            if (json_obj.count("mag")) {
                nlohmann::json mag_obj = json_obj.at("mag");
                nlohmann::json mag_data_obj = mag_obj.at("data");
                nlohmann::json last_mag_data_obj = *(mag_data_obj.rbegin());
                nlohmann::json last_mag_data_content = last_mag_data_obj[1];
                std::vector<double> mag = last_mag_data_content.get<std::vector<double>>();
                std::cout << "mag: (" << mag[0] << " , " << mag[1] << " , " << mag[2] << ")    ";
            }

            if (json_obj.count("rot_vector")) {
                nlohmann::json rot_vector_obj = json_obj.at("rot_vector");
                nlohmann::json rot_vector_data_obj = rot_vector_obj.at("data");
                nlohmann::json last_rot_vector_data_obj = *(rot_vector_data_obj.rbegin());
                nlohmann::json last_rot_vector_data_content = last_rot_vector_data_obj[1];
                std::vector<double> rot_vector = last_rot_vector_data_content.get<std::vector<double>>();
                std::cout << "rot_vector: (" << rot_vector[0] << " , " << rot_vector[1] << " , " << rot_vector[2]
                          << " , " << rot_vector[3] << ")   ";
                geometry_msgs::Quaternion quaternion;
                quaternion.x = (rot_vector[0]);
                quaternion.y = (rot_vector[1]);
                quaternion.z = (rot_vector[2]);
                quaternion.w = (rot_vector[3]);
                double roll, pitch, yaw;
                tf::Matrix3x3(tf::Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w))
                        .getRPY(roll, pitch, yaw);
                roll = roll / PI * 180;
                pitch = pitch / PI * 180;
                yaw = yaw / PI * 180;
                if (yaw < 0) yaw *= -1;
                else yaw = 360 - yaw;
                std::cout << "roll: " << roll << " pitch: " << pitch << " yaw: " << yaw << std::endl;
                gps_ned_data.pose.orientation = tf::createQuaternionMsgFromYaw(tfRadians(90 - yaw));
            }
            std::cout << std::endl;
        }
    }

    static void doubleToHex(vector<uint8_t> &byte_string,
                            int &value,
                            int length) {
        auto *hex_buffer = new uint8_t[length];
        mempcpy((char *) hex_buffer, (char *) &value, sizeof(int));
        int i;
        for (i = 0; i < length; ++i)
            byte_string.push_back(hex_buffer[i]);
    }

    static void decodeHex(const vector<uint8_t> &num8,
                          int position,
                          int length,
                          int32_t &num32) {
        if (length == 4)
            num32 = num8[position] | (num8[position + 1] << 8u) | (num8[position + 2] << 16u) |
                    (num8[position + 3] << 24u);
        else if (length == 1) {
            num32 = num8[position];
            if (num32 > 127) num32 -= 256;
        } else if (length == 2)
            num32 = num8[position] | (num8[position + 1] << 8u);
        else if (length == 3)
            num32 = num8[position] | (num8[position + 1] << 8u) | (num8[position + 2] << 16u);
        else;
    }

    void processNED(const std::string &str_receive,
                    geometry_msgs::PoseStamped &gps_ned_data) {
        std::vector<uint8_t> str_recv(str_receive.begin(), str_receive.end());
        if (str_recv[0] == 0xB5 && str_recv[1] == 0x62 && str_recv.size() > 45) {
            int OFFSET = 6;

            int32_t relPosN;
            decodeHex(str_recv, 8 + OFFSET, 4, relPosN);

            int32_t relPosE;
            decodeHex(str_recv, 12 + OFFSET, 4, relPosE);

            int32_t relPosD;
            decodeHex(str_recv, 16 + OFFSET, 4, relPosD);

            int32_t relPosLength;
            decodeHex(str_recv, 20 + OFFSET, 4, relPosLength);

            int32_t relPosHeading;
            decodeHex(str_recv, 24 + OFFSET, 4, relPosHeading);

            int32_t relPosHPN;
            decodeHex(str_recv, 32 + OFFSET, 1, relPosHPN);

            int32_t relPosHPE;
            decodeHex(str_recv, 33 + OFFSET, 1, relPosHPE);

            int32_t relPosHPD;
            decodeHex(str_recv, 34 + OFFSET, 1, relPosHPD);

            int32_t relPosHPLength;
            decodeHex(str_recv, 35 + OFFSET, 1, relPosHPLength);

            double rel_pos_N = ((double) relPosN + (double) relPosHPN * 0.01) * 0.01;
            double rel_pos_E = ((double) relPosE + (double) relPosHPE * 0.01) * 0.01;
            double rel_pos_D = ((double) relPosD + (double) relPosHPD * 0.01) * 0.01;
            double rel_pos_length = ((double) relPosLength + (double) relPosHPLength * 0.01) * 0.01;

            gps_ned_data.pose.position.x = rel_pos_N;
            gps_ned_data.pose.position.y = rel_pos_E;
            gps_ned_data.pose.position.z = rel_pos_D;

            gps_NED_publisher_.publish(gps_ned_data);
        }
    }

    static void computeChecksum(vector<uint8_t> &byte_string) {
        size_t i;
        uint8_t ck_a = 0;
        uint8_t ck_b = 0;

        for (i = 2; i < byte_string.size(); i++) {
            ck_a += byte_string[i];
            ck_b += ck_a;
        }
        byte_string.push_back(ck_a);
        byte_string.push_back(ck_b);
    }

    static std::string initFromHex(const std::initializer_list<uint8_t> &data) {
        return std::string(data.begin(), data.end());
    }

    static void convertStringToHex(const std::string &s,
                                   std::vector<uint8_t> &byte_string) {
        std::vector<std::string> v;
        findElementInSentence(s, v);

        for (const auto &str : v) {
            std::stringstream str_hex;
            str_hex << str;
            int value;
            str_hex >> std::hex >> value;
            byte_string.push_back(static_cast<uint8_t >(value));
        }
    }

    void generateSurverInCommand() {
        std::string result_str = initFromHex(
                {0xB5, 0x62, 0x06, 0x71, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x01, 0x00, 0x00,
                 0x20, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x62});
        serial_.write(result_str);
    }

    void generateDisableCommand() {
        std::string result_str = initFromHex(
                {0xB5, 0x62, 0x06, 0x71, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x93, 0xB5, 0x62, 0x06,
                 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x31,
                 0xBF});
        serial_.write(result_str);
    }

    void generateFrequencyCommand() {
        std::string result_str = initFromHex(
                {0xB5, 0x62, 0x06, 0x3E, 0x2C, 0x00, 0x00, 0x00, 0x3C, 0x05, 0x00, 0x08, 0x10, 0x00, 0x01, 0x00, 0x11,
                 0x01, 0x02, 0x0A, 0x12, 0x00, 0x00, 0x00, 0x21, 0x01, 0x03, 0x04, 0x05, 0x00, 0x01, 0x00, 0x11, 0x01,
                 0x05, 0x00, 0x04, 0x00, 0x01, 0x00, 0x11, 0x01, 0x06, 0x08, 0x0C, 0x00, 0x01, 0x00, 0x11, 0x01, 0x84,
                 0xBA, 0xB5, 0x62, 0x06, 0x8A, 0x0A, 0x00, 0x00, 0x07, 0x00, 0x00, 0x01, 0x00, 0x21, 0x30, 0x64, 0x00,
                 0x57, 0xEF});
        serial_.write(result_str);
    }

    void generateSerialCommand(const double &lat,
                               const double &lon,
                               const double &alt) {

        std::vector<uint8_t> byte_string;
        convertStringToHex("B5,62,06,71,28,00,00,00,02,01", byte_string);

        int lat_long = (int) (lat * 1e7);
        int lon_long = (int) (lon * 1e7);
        int alt_long = (int) (alt * 1e2);
        auto lat_short = (int) ((lat * 1e7 - lat_long) * 1e2);
        auto lon_short = (int) ((lon * 1e7 - lon_long) * 1e2);
        auto alt_short = (int) ((alt * 1e2 - alt_long) * 1e2);

        doubleToHex(byte_string, lat_long, 4);
        doubleToHex(byte_string, lon_long, 4);
        doubleToHex(byte_string, alt_long, 4);
        doubleToHex(byte_string, lat_short, 1);
        doubleToHex(byte_string, lon_short, 1);
        doubleToHex(byte_string, alt_short, 1);

        convertStringToHex("00,10,27,00,00,00,00,00,00,00,00,00"
                           "00,00,00,00,00,00,00,00,00", byte_string);

        computeChecksum(byte_string);
        std::string result_str(byte_string.begin(), byte_string.end());
        serial_.write(result_str);
    }

    void startRateCheckThread() {
        rate_check_thread_ = std::thread([this]() {
            stop_thread_flag_ = false;
            ros::NodeHandle node;
            ros::Rate rate(10.0);
            while (node.ok() && !stop_thread_flag_) {
                {
                    std::lock_guard<std::mutex> lock(last_available_time_mutex_);
                    ros::Time now = ros::Time::now();
                    if (last_txt_base_available_time_ != ros::Time() &&
                        now - last_txt_base_available_time_ > ros::Duration(2, 0)) {
                        ROS_WARN("GNTXT BASE received delay!");
                    }
                    if (last_txt_rover_available_time_ != ros::Time() &&
                        now - last_txt_rover_available_time_ > ros::Duration(2, 0)) {
                        ROS_WARN("GNTXT ROVER received delay!");
                    }
                }
                rate.sleep();
            }
        });
    }

private:
    ros::NodeHandle node_;

    serial::Serial serial_; // from serial
    ros::Subscriber sentence_subscriber_; // from topic

    ros::Publisher gps_NED_publisher_;
    ros::Publisher gps_GGA_publisher_;
    ros::Publisher gps_odom_publisher_;

    ros::Time package_timestamp_;
    vector<std::string> sentences_package_;

    ros::Time last_txt_base_available_time_;
    ros::Time last_txt_rover_available_time_;
    std::mutex last_available_time_mutex_;
    std::thread rate_check_thread_;
    std::atomic_bool stop_thread_flag_;

    geometry_msgs::PoseStamped gps_odom_data_;

};


int main(int argc, char **argv) {
    ros::init(argc, argv, "rtk_gps_node");
    ros::Time::init();
    ros::Rate loop_rate(50);

    RtkGpsNode n;
    if (argc == 3 && !strcmp(argv[1], "-m") && !strcmp(argv[2], "topic")) {
        ROS_INFO("Receive string from topic: /nmea_sentence ...");
        ros::spin();
    } else if (argc == 3 && !strcmp(argv[1], "-c")) {
        ROS_INFO("Receive string from serial ...");
        n.openSerial("/dev/ttyUSB0");
        n.writeCommand(argv[2]);
        while (ros::ok()) {
            n.readSerialSentence();
            loop_rate.sleep();
        }
    } else {
        ROS_ERROR("Missing argument.");
    }

    return 0;
}
