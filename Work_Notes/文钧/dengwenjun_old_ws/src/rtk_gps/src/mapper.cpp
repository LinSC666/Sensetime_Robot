#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <nmea_msgs/Gpgga.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <climits>
#include "nav_msgs/GetMap.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/Quaternion.h"
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/NavSatFix.h>

using namespace std;

static double kEarthRadius = 6378137;
static double PI = 3.1415926;

class GpsMapper {

private:
    geometry_msgs::PoseStamped zero_point_;
    vector<geometry_msgs::PoseStamped> gps_coordinates_path_;
    vector<cv::Point2f> world_coordinates_path_;
    double resolution_ = 0.05;
    double origin_[3] = {0, 0, 0};
    int negate_ = 0;
    double occupied_thresh_ = 0.65;
    double free_thresh_ = 0.196;
    int map_width_;
    int map_height_;
    double max_distance_ = LONG_MIN;
    double SCALAR_SIZE_ = 1.05;
    vector<cv::Point> map_points_;

    static double rad(double d) {
        return d * PI / 180.0;
    }

    static void Line(cv::Mat img,
                     const cv::Point &start,
                     const cv::Point &end,
                     const cv::Scalar_<double> &color) {
        int thickness = 1;
        int lineType = 16;
        line(img, start, end, color, thickness, lineType);
    }

    static double getDistance(const sensor_msgs::NavSatFix &point1,
                              const sensor_msgs::NavSatFix &point2) {
        double radLat1 = rad(point1.latitude);
        double radLat2 = rad(point2.latitude);
        double a = radLat1 - radLat2;
        double b = rad(point1.longitude) - rad(point2.longitude);
        double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
        s *= kEarthRadius;
        return s;
    }

    double getXYCoordinate(const vector<geometry_msgs::PoseStamped> &gps_path_point,
                           vector<cv::Point2f> &xy_point) {
        if (!xy_point.empty())
            vector<cv::Point2f>().swap(xy_point);
        for (const auto &point : gps_path_point) {
            xy_point.emplace_back(cv::Point2f(point.pose.position.x - zero_point_.pose.position.x,
                                              point.pose.position.y - zero_point_.pose.position.y));
        }
    }

    static double getXYCoordinate(const vector<sensor_msgs::NavSatFix> &gps_path_point,
                                  vector<cv::Point2f> &xy_point,
                                  const sensor_msgs::NavSatFix &zero_point) {
        if (!xy_point.empty())
            vector<cv::Point2f>().swap(xy_point);

        for (const auto &point : gps_path_point) {
            double b = rad(point.longitude) - rad(zero_point.longitude);
            double s = 2 * asin(sqrt(pow(cos(rad(zero_point.latitude)), 2) * pow(sin(b / 2), 2)));
            s *= kEarthRadius;
            double x;
            if (b < 0) x = -s;
            else x = s;

            double radLat1 = rad(point.latitude);
            double radLat2 = rad(zero_point.latitude);
            double a = radLat1 - radLat2;
            s = 2 * asin(sqrt(pow(sin(a / 2), 2)));
            s *= kEarthRadius;
            double y;
            if (a < 0) y = -s;
            else y = s;

            xy_point.emplace_back(cv::Point2f(x, y));
        }
    }


    void calculateMaxPoint(const geometry_msgs::PoseStamped &path_point) {
        if (max_distance_ < abs(path_point.pose.position.x)) max_distance_ = abs(path_point.pose.position.x);
        if (max_distance_ < abs(path_point.pose.position.y)) max_distance_ = abs(path_point.pose.position.y);
    }

    void calculateResolution() {
        vector<cv::Point2f> map_boundary;
        vector<geometry_msgs::PoseStamped> gps_boundary;
        geometry_msgs::PoseStamped vertex_point;
        vertex_point.pose.position.x = max_distance_;
        vertex_point.pose.position.y = max_distance_;
        gps_boundary.push_back(vertex_point);
        getXYCoordinate(gps_boundary, map_boundary);
        double abs_max_distance = abs(map_boundary[0].x);
        map_height_ = 2 * (int) (abs_max_distance / 0.04);
        map_width_ = map_height_;
        resolution_ = 2 * (abs_max_distance * SCALAR_SIZE_) / (double) map_height_;
        origin_[0] = -abs_max_distance * SCALAR_SIZE_;
        origin_[1] = origin_[0];
    }

public:
    cv::Mat map_;

    explicit GpsMapper(int height = 1000, int width = 1000) {
        map_height_ = height;
        map_width_ = width;
        map_ = cv::Mat(cv::Size(map_width_, map_height_), CV_8U, cv::Scalar(0));

        zero_point_.pose.position.x = 0;
        zero_point_.pose.position.y = 0;
        cv::namedWindow("map", 0);
    }

    ~GpsMapper() {
        clearPathPoints();
    }

    void addPathPoints(const geometry_msgs::PoseStamped &path_point) {
        gps_coordinates_path_.push_back(path_point);
        calculateMaxPoint(path_point);
    }

    void buildMap(nav_msgs::OccupancyGrid &occupancy_grid) {
        getXYCoordinate(gps_coordinates_path_, world_coordinates_path_);
        calculateResolution();
        vector<cv::Point>().swap(map_points_);
        cv::Mat temp_map = cv::Mat(cv::Size(map_width_, map_height_), CV_8U, cv::Scalar(0));

        for (const auto &point : world_coordinates_path_) {
            int x = (int) (point.x / resolution_) + map_width_ / 2;
            int y = (int) (point.y / resolution_) + map_height_ / 2;
            if (x < map_width_ && x >= 0 && y < map_height_ && y >= 0) {
                map_points_.emplace_back(cv::Point(x, y));
                temp_map.at<uchar>(y, x) = 255;
            }
        }

        if (map_points_.empty())
            return;
        for (size_t i = 0; i < map_points_.size() - 1; ++i) {
            Line(temp_map, map_points_[i], map_points_[i + 1], cv::Scalar(255));
        }
        vector<vector<cv::Point>> contours;
        vector<cv::Vec4i> hierarchy;
        cv::findContours(temp_map, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

        if (contours.empty())
            return;
        map_ = cv::Mat(cv::Size(map_width_, map_height_), CV_8U, cv::Scalar(100));
        cv::drawContours(map_, contours, 0, cv::Scalar(0), -1);
        vector<signed char> map_data;
        for (int i = 0; i < map_width_; ++i)
            for (int j = 0; j < map_height_; ++j) {
                map_data.push_back(map_.at<uchar>(i, j));
            }

        occupancy_grid.data = map_data;
        occupancy_grid.info.height = map_height_;
        occupancy_grid.info.width = map_width_;
        occupancy_grid.info.resolution = resolution_;
        occupancy_grid.info.origin.position.x = origin_[0];
        occupancy_grid.info.origin.position.y = origin_[1];
        occupancy_grid.info.origin.position.z = 0;
        occupancy_grid.info.origin.orientation = tf::createQuaternionMsgFromYaw(origin_[2]);
        occupancy_grid.header.frame_id = "/map";

        cv::addWeighted(temp_map, 0.6, map_, 0.4, 0, temp_map);

        cv::imshow("map", temp_map);
        cv::waitKey(1);

    }

    void clearPathPoints() {
        vector<geometry_msgs::PoseStamped>().swap(gps_coordinates_path_);
        vector<cv::Point2f>().swap(world_coordinates_path_);
    }

    int pathPointsSize() {
        return gps_coordinates_path_.size();
    }

};
