#include "apf/atificial_potential_field.h"
//#include "velocity_msg_.pb.h"

using namespace std;
using namespace gos;

//double robot_x;
//double robot_y;
//double robot_yaw;

ArtificialPotentialField::ArtificialPotentialField(const ros::NodeHandle& n)
    : linear_(0), angular_(0),
      pi_(3.14159265358979323846),
      n_(n), loop_rate_(20), loop_freq_(20), robot_radius_(0.16),v_max_(0.4)
{
  ROS_INFO("Create class ArtificialPotentialField!");
  robot_x_=0;
  robot_y_=0;
  robot_yaw_=0;
  // attraction
  n_.getParam("target_x", target_x_);
  ROS_INFO("target_x_ = %f", target_x_);
  n_.getParam("target_y", target_y_);
  ROS_INFO("target_y_ = %f", target_y_);
  n_.getParam("target_threshold", target_threshold_);
  ROS_INFO("target_threshold_ = %f", target_threshold_);
  n_.getParam("target_gain", target_gain_);
  ROS_INFO("target_gain_ = %f", target_gain_);
  
  // repulsion
  n_.getParam("obstacle_x", obstacle_x_);
  ROS_INFO("obstacle_x_ = %f", obstacle_x_);
  n_.getParam("obstacle_y", obstacle_y_);
  ROS_INFO("obstacle_y_ = %f", obstacle_y_);
  n_.getParam("obstacle_threshold", obstacle_threshold_);
  ROS_INFO("obstacle_threshold_ = %f", obstacle_threshold_);
  n_.getParam("obstacle_gain", obstacle_gain_);
  ROS_INFO("obstacle_gain_ = %f", obstacle_gain_);

  // debug
  n_.getParam("pub_state", pub_state_);
  ROS_INFO_STREAM("pub_state_ = " << pub_state_);

  //vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  shm_vel_pub = node.CreatePublisher<demo::twist>("vel", "vel_sub");
 // odom_sub_= n_.subscribe("/odom", 1, &ArtificialPotentialField::odomCallback,this);
 // shm_vel_pub.advertiser<demo::twist>("topic_1","/home/gophield/linsc_ws/src/gos_config.json");
  odom_subscriber =node.CreateSubscriber<demo::odometry>("odom", "odom_sub", 100,shm_odomCallback);
}

ArtificialPotentialField::~ArtificialPotentialField() {}

void ArtificialPotentialField::loop(void)
{
  Bivector robot_pos, obstacle_pos, target_pos;
  Bivector repulsion,attraction;
  Bivector apf_result;

  // visualization
  ros::Publisher robot_marker_pub = n_.advertise<visualization_msgs::Marker>("/robot",1);
  visualization_msgs::Marker robot_marker;
  initRobotMarkerVals(robot_marker);
  robot_marker.points.clear();
  robot_marker.pose.position.x = robot_x_;
  robot_marker.pose.position.y = robot_y_;
  robot_marker_pub.publish(robot_marker);
  ros::Publisher arrow_marker_pub = n_.advertise<visualization_msgs::Marker>("/arrow",1);
  visualization_msgs::Marker arrow_marker;
  initArrowMarkerVals(arrow_marker);
  arrow_marker.points[0].x = robot_x_;
  arrow_marker.points[0].y = robot_y_;
  arrow_marker.points[1].x = robot_x_+0.3*cos(robot_yaw_);
  arrow_marker.points[1].y = robot_y_+0.3*sin(robot_yaw_);
  arrow_marker_pub.publish(arrow_marker);
  ros::Publisher obstacle_marker_pub = n_.advertise<visualization_msgs::Marker>("/obstacle",1);
  visualization_msgs::Marker obstacle_marker;
  initObstacleMarkerVals(obstacle_marker);
  obstacle_marker.points.clear();
  obstacle_marker.pose.position.x = obstacle_x_;
  obstacle_marker.pose.position.y = obstacle_y_;
  obstacle_marker_pub.publish(obstacle_marker);

   //ros::Duration(1).sleep();
  while(ros::ok()) {
    robot_pos = Bivector(robot_x_,robot_y_);
    obstacle_pos = Bivector(obstacle_x_,obstacle_y_);
    target_pos = Bivector(target_x_,target_y_);

    repulsion = calculateRepulsion(robot_pos,obstacle_pos);
    attraction = calculateAttraction(robot_pos,target_pos);
    apf_result = repulsion+attraction;

    calculateLinearAngular(apf_result,linear_,angular_);

    // print result
  /*  std::cout << "robot_pos: x = " << robot_x_;
    std::cout << ", y = " << robot_y_ << ", yaw = " << robot_yaw_/pi_*180 << std::endl;;
    std::cout << "repulsion: ";
    repulsion.showBivector();
    std::cout << "attraction: ";
    attraction.showBivector();
    std::cout << "apf_result: ";
    apf_result.showBivector();
    std::cout << "desired_yaw = " << apf_result.getAngle()/pi_*180 << std::endl;*/
  //  std::cout << "linear = " << linear_ << ", angular = " << angular_ << std::endl;
    //std::cout<<std::endl;

    // simulation 
   /* robot_x_ = robot_x_+linear_*(1/loop_freq_)*cos(robot_yaw_);
    robot_y_ = robot_y_+linear_*(1/loop_freq_)*sin(robot_yaw_);
    robot_yaw_ = robot_yaw_+angular_*(1/loop_freq_);
    // visualization
    robot_marker.pose.position.x = robot_x_;
    robot_marker.pose.position.y = robot_y_;
    robot_marker_pub.publish(robot_marker);
    arrow_marker.points[0].x = robot_x_;
    arrow_marker.points[0].y = robot_y_;
    arrow_marker.points[1].x = robot_x_+0.3*cos(robot_yaw_);
    arrow_marker.points[1].y = robot_y_+0.3*sin(robot_yaw_);
    arrow_marker_pub.publish(arrow_marker);
    obstacle_marker_pub.publish(obstacle_marker);
*/
    // publish toppic 
    
    
   // vel_msg_.linear.x = linear_;
   // vel_msg_.angular.z = angular_;

    shm_msg_vel_.set_linear_x( linear_);
    shm_msg_vel_.set_angular_z(angular_);
    //shm_msg_vel_.SerializeToString(&shm_msg_vel_);
    
    if(pub_state_)
    {
     //cout<<"sc_velocity: "<<linear_<<"  sc_angular: "<<angular_<<"  "<<cnum_++<<endl;
     cout<<shm_msg_vel_.linear_x()<<"  "<<shm_msg_vel_.angular_z()<<"  "<<cnum_++<<"\n"<<endl;
     
      // vel_pub_.publish(vel_msg_);//ros
       shm_vel_pub->Publish(shm_msg_vel_);//shm
    }
   // robot_x_ = robot_x;
  //  robot_y_ = robot_y;
  //  robot_yaw_ = robot_yaw;
    //node.Spin();
    node.SpinOnce();
    ros::spinOnce();
    loop_rate_.sleep();
  }
}


void shm_odomCallback(const demo::odometry &odom_msg)
{
  ++count_num;                    
/*
  cout<<"callback_pose_position_x: "<< odom_msg.pose_pose_position_x()<<endl;
  cout<<"callback_pose_position_y: "<< odom_msg.pose_pose_position_y()<<endl;
  cout<<"callback_pose_pose_orientation_x: "<< odom_msg.pose_pose_orientation_x()<<endl;
  cout<<"callback_pose_pose_orientation_y: "<< odom_msg.pose_pose_orientation_y()<<endl;
  cout<<"callback_pose_pose_orientation_z: "<< odom_msg.pose_pose_orientation_z()<<endl;
  cout<<"callback_pose_pose_orientation_w: "<< odom_msg.pose_pose_orientation_w()<< "\n\n"<<endl;
 */
/*
  ROS_INFO("*******************shm_odom_apf**********************\n");
  printf("%.13f\n",odom_msg.pose_pose_position_x());
  printf("%.13f\n",odom_msg.pose_pose_position_y());
  printf("%.13f\n",odom_msg.pose_pose_orientation_x());
  printf("%.13f\n",odom_msg.pose_pose_orientation_y());
  printf("%.13f\n",odom_msg.pose_pose_orientation_z());
  printf("%.13f\n",odom_msg.pose_pose_orientation_w());
  ROS_INFO("-----------------------------------------------------\n");
*/
  printf("**************odom_callback******************\n");
  std::cout << count_num << std::endl; 
  robot_x_ =  odom_msg.pose_pose_position_x();
  robot_y_ = odom_msg.pose_pose_position_y();

  // quaternion to yaw
  double qx =  odom_msg.pose_pose_orientation_x();
  double qy =  odom_msg.pose_pose_orientation_y();
  double qz =  odom_msg.pose_pose_orientation_z();
  double qw =  odom_msg.pose_pose_orientation_w();
  double a = 2.0*(qw*qz+qx*qy);
  double b = 1.0-2.0*(qy*qy+qz*qz);
  robot_yaw_ = atan2(a, b);
  /*ROS_WARN("Odometry: ");
  std::cout << "x = " << robot_x_ << ", y = " << robot_y_ 
            << ", yaw = " << robot_yaw_/3.14159*180 << std::endl;
  */

}

void ArtificialPotentialField::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
/*
  ROS_INFO("*****************ros_odom_apf***********************\n");
  printf("%.13f\n",msg->pose.pose.position.x);
  printf("%.13f\n",msg->pose.pose.position.y);
  printf("%.13f\n",msg->pose.pose.orientation.x);
  printf("%.13f\n",msg->pose.pose.orientation.y);
  printf("%.13f\n",msg->pose.pose.orientation.z);
  printf("%.13f\n",msg->pose.pose.orientation.w);
  ROS_INFO("----------------------------------------------------\n");
*/
  robot_x_ = msg->pose.pose.position.x;
  robot_y_ = msg->pose.pose.position.y;

  // quaternion to yaw
  double qx = msg->pose.pose.orientation.x;
  double qy = msg->pose.pose.orientation.y;
  double qz = msg->pose.pose.orientation.z;
  double qw = msg->pose.pose.orientation.w;
  double a = 2.0*(qw*qz+qx*qy);
  double b = 1.0-2.0*(qy*qy+qz*qz);
  robot_yaw_ = atan2(a, b);
 // std::cout << "x = " << robot_x_ << ", y = " << robot_y_ 
 //           << ", yaw = " << robot_yaw_/3.14159*180 << std::endl;

 //  shm_odom_sub.subscribe("topic_2","gos.sub.node2.topic_2.sub1",shm_odomCallback);
}

ArtificialPotentialField::Bivector ArtificialPotentialField::calculateRepulsion(const Bivector& robot_position, const Bivector& obstacle_position)
{
  Bivector dp = robot_position-obstacle_position;
  double dis = dp.norm();
  // dp = dp-robot_radius_*(dp/dis); // convert workspace into configuration space
  dp = (1-robot_radius_/dis)*dp;  // convert workspace into configuration space
  dis = dp.norm();

  Bivector gradient;
  if(dis>obstacle_threshold_) {
    gradient = Bivector(0,0);
  }
  else {
    double gain = obstacle_gain_*(1/obstacle_threshold_-1/dis)/(dis*dis*dis);
    gradient = gain*dp;
  }
  return -gradient;
}

ArtificialPotentialField::Bivector ArtificialPotentialField::calculateAttraction(const Bivector& robot_position, const Bivector& target_position)
{
  Bivector dp = robot_position-target_position;
  double dis = dp.norm();

  Bivector gradient;
  if(dis>target_threshold_) {
    double gain = target_threshold_*target_gain_/dis;
    gradient = gain*dp;
  }
  else {
    gradient = target_gain_*dp;
  }
  return -gradient;
}

void ArtificialPotentialField::calculateLinearAngular(const Bivector& veloicity, double& linear, double& angular)
{
  Bivector vel(veloicity); 
  double speed = vel.norm();
  if(speed>v_max_) {
    // vel = v_max_*(vel/speed); // limit veloicity 
    vel = (v_max_/speed)*vel; // limit veloicity 
    speed = v_max_;
  }
  
  double vx=vel.getX();
  double vy=vel.getY();
  double desire_yaw = vel.getAngle();
  double delta_yaw = desire_yaw-robot_yaw_;
  delta_yaw = limitAngle(delta_yaw,0);
  double max_w = 1.3;   
  if(delta_yaw>pi_/8) {
    angular = max_w;
    linear = 0;
  }
  else if(delta_yaw<-pi_/8) {
    angular = -max_w;
    linear = 0;
  }
  else {
    angular = delta_yaw*3.33;
    linear = speed;
  }
}

double ArtificialPotentialField::limitAngle(double angle, double standard_angle)
{
  angle = angle + (pi_ - standard_angle);
  angle = angle - floor((angle)/(2*pi_))*(2*pi_);
  angle = angle - (pi_ - standard_angle);
  return angle;
}

void ArtificialPotentialField::initRobotMarkerVals(visualization_msgs::Marker& marker)
{
  marker.header.frame_id = "/map"; 
  marker.header.stamp = ros::Time();
  marker.ns = "";
  marker.id = 0;
  // use SPHERE if you only want a single marker
  // use SPHERE_LIST for a group of markers
  marker.type = visualization_msgs::Marker::CYLINDER; 
  marker.action = visualization_msgs::Marker::ADD;
  // if just using a single marker, specify the coordinates here, like this:

  // marker.pose.position.x = 0;
  // marker.pose.position.y = 0;
  // marker.pose.position.z = 0;

  //whether a single marker or list of markers, need to specify marker properties
  // these will all be the same for SPHERE_LIST
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.color.a = 1.0;
  marker.color.r = 0.0;
  marker.color.g = 1.0;
  marker.color.b = 0.0;

  double ra = robot_radius_;
  marker.scale.x = 2*ra;
  marker.scale.y = 2*ra;
  double height = 0.1;
  marker.scale.z = height;
  marker.pose.position.z = height/2;
}

void ArtificialPotentialField::initArrowMarkerVals(visualization_msgs::Marker& marker)
{
  marker.header.frame_id = "/map"; 
  marker.header.stamp = ros::Time();
  marker.ns = "";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::ARROW; 
  marker.action = visualization_msgs::Marker::ADD;
  
  marker.color.a = 1.0;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 1.0;

  marker.scale.x = 2*0.03;
  marker.scale.y = 2*0.06;
  marker.scale.z = 0.3/2;

  geometry_msgs::Point point;
  point.x = 0;
  point.y = 0;
  point.z = 0.1;
  marker.points.push_back(point);
  point.x = 0.3;
  point.y = 0;
  point.z = 0.1;
  marker.points.push_back(point);
}

void ArtificialPotentialField::initObstacleMarkerVals(visualization_msgs::Marker& marker)
{
  marker.header.frame_id = "/map"; // reference frame for marker coords
  marker.header.stamp = ros::Time();
  marker.ns = "";
  marker.lifetime = ros::Duration();
  marker.type = visualization_msgs::Marker::CYLINDER; //;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.color.a = 1.0;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  double ra = robot_radius_;
  marker.scale.x = 2*ra;
  marker.scale.y = 2*ra;
  double height = 0.5;
  marker.scale.z = height;
  marker.pose.position.z = height/2;
  
}


