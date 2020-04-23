#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/clock.hpp"

#include "sensor_msgs/msg/image.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"
#include <memory>

//*************************//
//By linsc
//*************************//


//rclcpp::Duration total_msec;     // 定义一个时间点
int cpu_rate;

rclcpp::Publisher<std_msgs::msg::String>::SharedPtr rec_pub;
auto rec_msg = std::make_shared<std_msgs::msg::String>();

void chatterCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
//  std::cout << "D2cpp:g" << std::endl;
  if(cpu_rate==1)
  {
   std::cout << "cpu1" << std::endl;
  system("ps -ef | grep /bin/sh | grep -v grep | awk '{print $2}' | xargs kill -9");
   cpu_rate=10;
     system("sh /root/ros2_ws/ros2_ws/killcpu.sh 1");
     
  }
  else if(cpu_rate==2)
  {
    std::cout << "cpu2" << std::endl;
 system("ps -ef | grep /bin/sh | grep -v grep | awk '{print $2}' | xargs kill -9");
 cpu_rate=10;
     system("sh /root/ros2_ws/ros2_ws/killcpu.sh 2");
     
  }
  else if(cpu_rate==3)
  {
    std::cout << "cpu3" << std::endl;
 system("ps -ef | grep /bin/sh | grep -v grep | awk '{print $2}' | xargs kill -9");
 cpu_rate=10;
     system("sh /root/ros2_ws/ros2_ws/killcpu.sh 3");
    
  }
  else if(cpu_rate==4)
  {
    std::cout << "cpu4" << std::endl;
  system("ps -ef | grep /bin/sh | grep -v grep | awk '{print $2}' | xargs kill -9");
  cpu_rate=10;
    system("sh /root/ros2_ws/ros2_ws/killcpu.sh 4");
   
  }
  else if(cpu_rate==0)
  {
    std::cout << "clean" << std::endl;
    system("ps -ef | grep /bin/sh | grep -v grep | awk '{print $2}' | xargs kill -9");
    cpu_rate=10;
  }


}

void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
          std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>      response)
{
  response->sum = request->a + request->b;
  cpu_rate=response->sum;
   rec_msg->data = std::to_string(cpu_rate);
      rec_pub->publish(rec_msg);
  std::cout <<cpu_rate<< "  add start!!!" << std::endl;
}


int main(int argc, char * argv[])
{
    //ros::init(argc, argv, "listener");
    rclcpp::init(argc, argv);

    //ros::NodeHandle n;
    auto node = rclcpp::Node::make_shared("l3");

    //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    auto image_sub = node->create_subscription<sensor_msgs::msg::Image>(
    "image_source/image_raw", chatterCallback, 10);

   //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_default;
    custom_qos_profile.depth = 10;
    rec_pub = node->create_publisher<std_msgs::msg::String>("D2cpp_pub", custom_qos_profile);


   rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
   node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

   rclcpp::spin(node);

    return 0;
}





















