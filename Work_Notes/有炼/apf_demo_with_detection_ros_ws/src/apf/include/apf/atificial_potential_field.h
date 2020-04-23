#ifndef _ARTIFICIAL_POTENTIAL_FIELD_H_
#define _ARTIFICIAL_POTENTIAL_FIELD_H_ 

#include <stdio.h>
#include <math.h>
#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include "am_msgs/DetectionResult.h"
#include "am_msgs/Object.h"

class ArtificialPotentialField 
{
public:
  ArtificialPotentialField(const ros::NodeHandle& n);
  ~ArtificialPotentialField();

  void loop();
private:
  class Bivector 
  {
    public:
      explicit Bivector(double x_in = 0, double y_in = 0):x(x_in),y(y_in) {};
      Bivector(const Bivector& p):x(p.x),y(p.y) {};
      ~Bivector(){};
      Bivector operator-(void) {x = -x; y = -y; return*this;};
      Bivector operator=(const Bivector& p) {x = p.x; y = p.y;return *this;};
      Bivector operator+(const Bivector& p) const {return Bivector(x+p.x,y+p.y);};
      Bivector operator-(const Bivector& p) const {return Bivector(x-p.x,y-p.y);};
      Bivector operator*(double gain) const {return Bivector(gain*x,gain*y);};
      friend Bivector operator*(double gain,const Bivector& p) {return Bivector(gain*p.x,gain*p.y);};
      Bivector operator/(double divisor) const {return Bivector(x/divisor,y/divisor);};
      double norm() const {return sqrt(x*x+y*y);};
      double getX() const {return x;};
      double getY() const {return y;};
      double getAngle() const {return atan2(y,x);};
      void showBivector() const {std::cout<<"x = "<<x<<" , y = "<<y<<std::endl;};
    private:
      double x;
      double y;
  };

  // ROS node
  ros::NodeHandle n_;
  ros::Rate loop_rate_;
  double loop_freq_;

  // publish vel_cmd
  ros::Publisher vel_pub_;
  geometry_msgs::Twist vel_msg_;
  double linear_;
  double angular_;

  // subscribe odom
  ros::Subscriber odom_sub_;
  Bivector robot_pos_;
  double robot_yaw_;

  // subscribe detection, repulsion
  ros::Subscriber obs_sub_;
  am_msgs::DetectionResult obs_msg_;
  Bivector obstacle_pos_;
  std::vector<Bivector> obstacles_pos_;
  double obstacle_threshold_;
  double obstacle_gain_;
  
  // attraction
  Bivector target_pos_;
  double target_threshold_;
  double target_gain_;

  // debug
  int is_pub_vel_;
  int is_visulized_;
  int is_simulated_;

  // robot parameter
  double robot_radius_;
  double v_max_;  // maximun speed of the wheel

  // pi
  const double pi_;

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
  void obsCallback(const am_msgs::DetectionResult::ConstPtr& msg);
  Bivector calculateRepulsion(const Bivector& robot_position, const Bivector& obstacle_position);
  Bivector calculateRepulsion(const Bivector& robot_position, const std::vector<Bivector>& obstacles_position);
  Bivector calculateAttraction(const Bivector& robot_position, const Bivector& target_position);
  void calculateLinearAngular(const Bivector& veloicity, double& linear, double& angular);
  double limitAngle(double angle, double standard_angle);
  void initRobotMarkerVals(visualization_msgs::Marker& marker);
  void initArrowMarkerVals(visualization_msgs::Marker& marker);
  void initObstacleMarkerVals(visualization_msgs::Marker& marker);
};


#endif
