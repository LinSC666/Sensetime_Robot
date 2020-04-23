 #include "apf/atificial_potential_field.h"

ArtificialPotentialField::ArtificialPotentialField(const ros::NodeHandle& n)
    : linear_(0), angular_(0),
      pi_(3.14159265358979323846),
      n_(n), loop_rate_(20), loop_freq_(20)
{
  ROS_INFO("Create class ArtificialPotentialField!");
  
  // debug
  n_.getParam("is_pub_vel", is_pub_vel_);
  ROS_INFO_STREAM("is_pub_vel_ = " << is_pub_vel_);
  n_.getParam("is_visulized", is_visulized_);
  ROS_INFO_STREAM("is_visulized_ = " << is_visulized_);
  n_.getParam("is_simulated", is_simulated_);
  ROS_INFO_STREAM("is_simulated_ = " << is_simulated_);

  // robot parameter
  n_.getParam("robot_radius", robot_radius_);
  ROS_INFO_STREAM("robot_radius_ = " << robot_radius_);
  n_.getParam("v_max", v_max_);
  ROS_INFO_STREAM("v_max_ = " << v_max_);

  // attraction
  double target_x, target_y;
  n_.getParam("target_x", target_x);
  ROS_INFO("target_x = %f", target_x);
  n_.getParam("target_y", target_y);
  ROS_INFO("target_y = %f", target_y);
  target_pos_ = Bivector(target_x, target_y);
  n_.getParam("target_threshold", target_threshold_);
  ROS_INFO("target_threshold_ = %f", target_threshold_);
  n_.getParam("target_gain", target_gain_);
  ROS_INFO("target_gain_ = %f", target_gain_);
  
  // repulsion
  double obstacle_x, obstacle_y;
  n_.getParam("obstacle_x", obstacle_x);
  ROS_INFO("obstacle_x = %f", obstacle_x);
  n_.getParam("obstacle_y", obstacle_y);
  ROS_INFO("obstacle_y = %f", obstacle_y);
  obstacles_pos_.push_back( Bivector(obstacle_x, obstacle_y) );

  n_.getParam("obstacle2_x", obstacle_x);
  ROS_INFO("obstacle_x = %f", obstacle_x);
  n_.getParam("obstacle2_y", obstacle_y);
  ROS_INFO("obstacle_y = %f", obstacle_y);
  obstacles_pos_.push_back( Bivector(obstacle_x, obstacle_y) );

  n_.getParam("obstacle_threshold", obstacle_threshold_);
  ROS_INFO("obstacle_threshold_ = %f", obstacle_threshold_);
  n_.getParam("obstacle_gain", obstacle_gain_);
  ROS_INFO("obstacle_gain_ = %f", obstacle_gain_);

  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  odom_sub_ = n_.subscribe("/odom", 1, &ArtificialPotentialField::odomCallback,this);
  // obs_sub_ = n_.subscribe("/detection_result", 1, &ArtificialPotentialField::obsCallback,this);
}

ArtificialPotentialField::~ArtificialPotentialField() {}

void ArtificialPotentialField::loop(void)
{
  Bivector repulsion,attraction;
  Bivector apf_result;

  // visualization
  ros::Publisher robot_marker_pub;
  visualization_msgs::Marker robot_marker;
  ros::Publisher arrow_marker_pub;
  visualization_msgs::Marker arrow_marker;
  ros::Publisher obstacle_marker_pub;
  visualization_msgs::Marker obstacle_marker;
  if(is_visulized_) {
    robot_marker_pub = n_.advertise<visualization_msgs::Marker>("/robot",1);
    initRobotMarkerVals(robot_marker);
    robot_marker.points.clear();
    robot_marker.pose.position.x = robot_pos_.getX();
    robot_marker.pose.position.y = robot_pos_.getY();
    robot_marker_pub.publish(robot_marker);
    arrow_marker_pub = n_.advertise<visualization_msgs::Marker>("/arrow",1);
    initArrowMarkerVals(arrow_marker);
    arrow_marker.points[0].x = robot_pos_.getX();
    arrow_marker.points[0].y = robot_pos_.getY();
    arrow_marker.points[1].x = robot_pos_.getX()+0.3*cos(robot_yaw_);
    arrow_marker.points[1].y = robot_pos_.getY()+0.3*sin(robot_yaw_);
    arrow_marker_pub.publish(arrow_marker);
    // obstacle_marker_pub = n_.advertise<visualization_msgs::Marker>("/obstacle",1);
    // initObstacleMarkerVals(obstacle_marker);
    // obstacle_marker.points.clear();
    // obstacle_marker.pose.position.x = obstacle_pos_.getX();
    // obstacle_marker.pose.position.y = obstacle_pos_.getY();
    // obstacle_marker_pub.publish(obstacle_marker);
  }

  //ros::Duration(1).sleep();
  while(ros::ok()) {
    
    // robot_pos_ and obstacles_pos_ will be updated in callback
    repulsion = calculateRepulsion(robot_pos_,obstacles_pos_);
    attraction = calculateAttraction(robot_pos_,target_pos_);
    apf_result = repulsion+attraction;

    calculateLinearAngular(apf_result,linear_,angular_);

    // print result
    std::cout << "robot_pos_: ";
    robot_pos_.showBivector();
    std::cout << "robot_yaw_: " << robot_yaw_ << std::endl; 
    std::cout << "obstacle_p: " << std::endl;
    for(auto iter=obstacles_pos_.begin();iter!=obstacles_pos_.end();iter++){
      std::cout << "\t";
      iter->showBivector();
    }
    std::cout << "repulsion: ";
    repulsion.showBivector();
    std::cout << "attraction: ";
    attraction.showBivector();
    std::cout << "apf_result: ";
    apf_result.showBivector();
    std::cout << "desired_yaw = " << apf_result.getAngle()/pi_*180 << std::endl;
    std::cout << "linear = " << linear_ << ", angular = " << angular_ << std::endl;
    std::cout << std::endl;

    // simulation 
    if(is_simulated_){
      double x = robot_pos_.getX();
      double y = robot_pos_.getY();
      x = x + linear_*(1/loop_freq_)*cos(robot_yaw_);
      y = y + linear_*(1/loop_freq_)*sin(robot_yaw_);
      robot_yaw_ = robot_yaw_+angular_*(1/loop_freq_);
      robot_pos_ = Bivector(x, y);
    }
    // visualization
    if(is_visulized_){
      robot_marker.pose.position.x = robot_pos_.getX();
      robot_marker.pose.position.y = robot_pos_.getY();
      robot_marker_pub.publish(robot_marker);
      arrow_marker.points[0].x = robot_pos_.getX();
      arrow_marker.points[0].y = robot_pos_.getY();
      arrow_marker.points[1].x = robot_pos_.getX()+0.3*cos(robot_yaw_);
      arrow_marker.points[1].y = robot_pos_.getY()+0.3*sin(robot_yaw_);
      arrow_marker_pub.publish(arrow_marker);
      // obstacle_marker_pub.publish(obstacle_marker);
    }

    // publish toppic 
    vel_msg_.linear.x = linear_;
    vel_msg_.angular.z = angular_;
    if(is_pub_vel_)
      vel_pub_.publish(vel_msg_);

    ros::spinOnce();
    loop_rate_.sleep();
  }
}

void ArtificialPotentialField::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  robot_pos_ = Bivector(msg->pose.pose.position.x, msg->pose.pose.position.y);

  // quaternion to yaw
  double qx = msg->pose.pose.orientation.x;
  double qy = msg->pose.pose.orientation.y;
  double qz = msg->pose.pose.orientation.z;
  double qw = msg->pose.pose.orientation.w;
  double a = 2.0*(qw*qz+qx*qy);
  double b = 1.0-2.0*(qy*qy+qz*qz);
  robot_yaw_ = atan2(a, b);
}

void ArtificialPotentialField::obsCallback(const am_msgs::DetectionResult::ConstPtr& msg)
{
  obstacles_pos_.clear();
  Bivector pos;
  for(auto iter=msg->objects.begin();iter!=msg->objects.end();iter++){
    // camera coordinate frame transform into body coordinate frame. X=y, Y=-x
    // body coordinate frame transform into world coordinate frame. X=x*cos-y*sin+x0, Y=x*sin+y*cos+y0
    // camera coordinate frame transform into world coordinate frame. X=x*sin+y*cos+x0, Y=-x*cos+y*sin+y0
    pos = Bivector(iter->position.x, iter->position.y);  // position on camera coordinate frame
    double X =  pos.getX()*sin(robot_yaw_)+pos.getY()*cos(robot_yaw_)+robot_pos_.getX();
    double Y = -pos.getX()*cos(robot_yaw_)+pos.getY()*sin(robot_yaw_)+robot_pos_.getY();
    obstacles_pos_.push_back(Bivector(X,Y));
  }
}

ArtificialPotentialField::Bivector ArtificialPotentialField::calculateRepulsion(const Bivector& robot_position, 
                                                  const Bivector& obstacle_position)
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
    // double gain = obstacle_gain_*(1/obstacle_threshold_-1/dis)/(dis*dis*dis);
    // gradient = gain*dp;
    double gain = (obstacle_gain_*dis - obstacle_gain_*obstacle_threshold_)/dis;
    gradient = gain*dp;
  }

  return -gradient;
}

ArtificialPotentialField::Bivector ArtificialPotentialField::calculateRepulsion(const Bivector& robot_position, 
                                                  const std::vector<Bivector>& obstacles_position)
{
  Bivector repulsion(0, 0);
  Bivector pos;
  for(auto iter=obstacles_position.begin();iter!=obstacles_position.end();iter++) {
    pos = *iter;
    repulsion = repulsion + calculateRepulsion(robot_position, pos);
  }
  return repulsion;
}

ArtificialPotentialField::Bivector ArtificialPotentialField::calculateAttraction(const Bivector& robot_position, 
                                                  const Bivector& target_position)
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
  if(delta_yaw>0.59) {
    angular = max_w;
    linear = 0;
  }
  else if(delta_yaw<-0.59) {
    angular = -max_w;
    linear = 0;
  }
  else {
    angular = delta_yaw*2.22;
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


