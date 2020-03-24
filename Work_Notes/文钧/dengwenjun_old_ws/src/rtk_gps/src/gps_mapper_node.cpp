#include "ros/ros.h"
#include <sensor_msgs/NavSatFix.h>
#include "mapper.cpp"
#include <serial/serial.h>
#include <std_msgs/String.h>
#include "nav_msgs/GetMap.h"

class GpsMapperNode {

public:
    GpsMapperNode() :
            node_("~"),
            gps_TXT_subscriber_(node_.subscribe("/gps_odom", 1, &GpsMapperNode::gpsTXTCallback, this)),
            gps_GGA_subscriber_(node_.subscribe("/gps_gga", 1, &GpsMapperNode::gpsGGACallback, this)),
            gps_map_publisher_(node_.advertise<nav_msgs::OccupancyGrid>("/map", 1000)) {}

    ~GpsMapperNode() {
        delete mapper_;
    }

    void gpsTXTCallback(const geometry_msgs::PoseStamped::ConstPtr &msg) {
        ROS_INFO("Topic gps_txt: position x is [%3.10f], position y is [%3.10f].", msg->pose.position.x, msg->pose.position.y);
        mapper_->addPathPoints(*msg);
        publishMap(msg->header.stamp);
    }

    void gpsGGACallback(const sensor_msgs::NavSatFix::ConstPtr &msg) {
        ROS_INFO("Topic gps_wgs: lat is [%3.10f], lon is [%3.10f].", msg->latitude, msg->longitude);
    }

private:
    ros::NodeHandle node_;
    ros::Subscriber gps_TXT_subscriber_;
    ros::Subscriber gps_GGA_subscriber_;
    ros::Publisher gps_map_publisher_;

    GpsMapper *mapper_ = new GpsMapper;

    void publishMap(const ros::Time &time) {
        nav_msgs::OccupancyGrid occupancy_grid;
        occupancy_grid.header.stamp = time;
        mapper_->buildMap(occupancy_grid);
        gps_map_publisher_.publish(occupancy_grid);
    }

    void clearPathPoints() {
        mapper_->clearPathPoints();
    }

};

int main(int argc, char **argv) {
    ros::init(argc, argv, "gps_mapper_node");

    GpsMapperNode n;

    ros::spin();
}
