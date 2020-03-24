#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "odometry.cpp"

class GpsOdometryNode {

public:
    GpsOdometryNode() :
            node_("~"),
            gps_NED_subscriber_(node_.subscribe("/gps_odom", 1, &GpsOdometryNode::gpsNEDCallback, this)),
	    phone_pose_subscriber_(node_.subscribe("/phone_pose", 1, &GpsOdometryNode::phonePoseCallback, this)),
            gps_odometry_publisher_(node_.advertise<nav_msgs::Odometry>("/odom", 50)) {
        odom_.pose.pose.position.x = 0;
        odom_.pose.pose.position.y = 0;
        odom_.pose.pose.position.z = 0;
        odom_.pose.pose.orientation = tf::createQuaternionMsgFromYaw(0);
    }

    ~GpsOdometryNode() {
        delete odometry_;
    }

    void phonePoseCallback(const geometry_msgs::Pose::ConstPtr &msg) {
        odometry_->updateOrientation(*msg);

        geometry_msgs::TransformStamped odom_trans;
        odometry_->generateTransform(odom_trans);
        gps_odom_broadcaster_.sendTransform(odom_trans);

        odometry_->generateOdomMessage(odom_);
        gps_odometry_publisher_.publish(odom_);
	
    }

    void gpsNEDCallback(const geometry_msgs::PoseStamped::ConstPtr &msg) {
        ROS_INFO("Topic gps_ned: x is [%3.10f], y is [%3.10f].", msg->pose.position.x, msg->pose.position.y);
        odometry_->updateTime(msg->header.stamp);
        odometry_->updateStatement(*msg);

        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = msg->header.stamp;
        odometry_->generateTransform(odom_trans);
        gps_odom_broadcaster_.sendTransform(odom_trans);

        odom_.header.stamp = msg->header.stamp;
        odometry_->generateOdomMessage(odom_);
        gps_odometry_publisher_.publish(odom_);
    }

private:
    ros::NodeHandle node_;
    ros::Subscriber gps_NED_subscriber_;
    ros::Subscriber phone_pose_subscriber_;
    ros::Publisher gps_odometry_publisher_;
    tf::TransformBroadcaster gps_odom_broadcaster_;

    GpsOdometry *odometry_ = new GpsOdometry;
    nav_msgs::Odometry odom_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "gps_odometry_node");

    GpsOdometryNode n;

    ros::spin();
}
