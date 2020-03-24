#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class GpsOdometry {

public:
    GpsOdometry() = default;

    ~GpsOdometry() = default;

    void updateTime(const ros::Time &time) {
        current_time_ = time;
        dt_ = (current_time_ - last_time_).toSec();
        last_time_ = current_time_;
    }

    void updateStatement(const geometry_msgs::PoseStamped &pose) {
        if (std::abs(pose.pose.position.x) < 1e-4 || std::abs(pose.pose.position.y) < 1e-4) {
            ROS_WARN("Pose value received too low!");
            return;
        }
        vx_ = (pose.pose.position.x - x_) / dt_;
        vy_ = (pose.pose.position.y - y_) / dt_;
        vz_ = (pose.pose.position.z - z_) / dt_;
        vyaw_ = (tf::getYaw(pose.pose.orientation) - yaw_) / dt_;
        x_ = pose.pose.position.x;
        y_ = pose.pose.position.y;
        z_ = pose.pose.position.z;
        yaw_ = tf::getYaw(pose.pose.orientation);
       // quaternion_ = pose.pose.orientation;

    }

    void updateOrientation(const geometry_msgs::Pose &pose) {
        quaternion_ = pose.orientation;
    }

    void generateTransform(geometry_msgs::TransformStamped &odom_trans) {
        odom_trans.header.frame_id = "/odom";
        odom_trans.child_frame_id = "/base_link";

        odom_trans.transform.translation.x = x_;
        odom_trans.transform.translation.y = y_;
        odom_trans.transform.translation.z = z_;
        odom_trans.transform.rotation = quaternion_;
    }

    void generateOdomMessage(nav_msgs::Odometry &odom) {
        odom.header.stamp = current_time_;
        odom.header.frame_id = "/odom";
        odom.child_frame_id = "/base_link";

        odom.pose.pose.position.x = x_;
        odom.pose.pose.position.y = y_;
        odom.pose.pose.position.z = z_;
        odom.pose.pose.orientation = quaternion_;

        odom.twist.twist.linear.x = vx_;
        odom.twist.twist.linear.y = vy_;
        odom.twist.twist.linear.z = vz_;
        odom.twist.twist.angular.x = vroll_;
        odom.twist.twist.angular.y = vpitch_;
        odom.twist.twist.angular.z = vyaw_;
    }

private:
    double x_ = 0.0;
    double y_ = 0.0;
    double z_ = 0.0;
    double vx_ = 0.0;
    double vy_ = 0.0;
    double vz_ = 0.0;

    double roll_ = 0.0;
    double pitch_ = 0.0;
    double yaw_ = 0.0;
    double vroll_ = 0.0;
    double vpitch_ = 0.0;
    double vyaw_ = 0.0;

    geometry_msgs::Quaternion quaternion_;

    ros::Time current_time_;
    ros::Time last_time_;
    double dt_ = 0;
};


