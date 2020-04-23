#ifndef _ARTIFICIAL_POTENTIAL_FIELD_H_
#define _ARTIFICIAL_POTENTIAL_FIELD_H_ 

#include <stdio.h>
#include <math.h>
#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include "gos.h"
#include "gos.cpp"
#include "velocity_msg_.pb.h"
#include "odom_msg_.pb.h"

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
      Bivector(double x_in = 0, double y_in = 0):x(x_in),y(y_in) {};
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
  //************************************//
  //shm
  int cnum_=0;
  gos::Publisher shm_vel_pub;
  demo::twist shm_msg_vel_;
  gos::Subscriber<demo::odometry> shm_odom_sub;  
  //************************************//

  ros::NodeHandle n_;
  ros::Rate loop_rate_;
  double loop_freq_;

  ros::Publisher vel_pub_;
  geometry_msgs::Twist vel_msg_;
  double linear_;
  double angular_;

  ros::Subscriber odom_sub_;
 // double robot_x_;
  //double robot_y_;
  //double robot_yaw_;
  
  // repulsion
  ros::Subscriber obs_sub_;
  double obstacle_x_;
  double obstacle_y_;
  double obstacle_threshold_;
  double obstacle_gain_;
  
  // attraction
  double target_x_;
  double target_y_;
  double target_threshold_;
  double target_gain_;

  // debug
  int pub_state_;

  // robot parameter
  double robot_radius_;
  double v_max_;  // maximun speed of the wheel

  //
  const double pi_;
  
  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
  Bivector calculateRepulsion(const Bivector& robot_position, const Bivector& obstacle_position);
  Bivector calculateAttraction(const Bivector& robot_position, const Bivector& target_position);
  void calculateLinearAngular(const Bivector& veloicity, double& linear, double& angular);
  double limitAngle(double angle, double standard_angle);
  void initRobotMarkerVals(visualization_msgs::Marker& marker);
  void initArrowMarkerVals(visualization_msgs::Marker& marker);
  void initObstacleMarkerVals(visualization_msgs::Marker& marker);
};

  double robot_x_;
  double robot_y_;
  double robot_yaw_;
void shm_odomCallback(const demo::odometry odom_msg);

#endif
