#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/clock.hpp"

//*************************//
//By linsc
//*************************//


long long int num=0;
rclcpp::Clock steady_clock(RCL_STEADY_TIME);
rclcpp::Time begin;
rclcpp::Time end;
//rclcpp::Duration total_msec;     // 定义一个时间点
float msec;

void chatterCallback(const std_msgs::msg::String::SharedPtr msg)
{
std::cout <<"linsc" << std::endl;
   num++;
    if(num==1000000)
   {
   std::cout << "start_ZMQ_linsc_effiency_test!!!..." << std::endl;
   end=steady_clock.now();   //获取结束时间
  msec=1000*((end -begin).seconds());

   printf("\nTotal elapsed time: %.2f msec\n",msec);
	exit(0);
   }
}

int main(int argc, char * argv[])
{
    //ros::init(argc, argv, "listener");
    rclcpp::init(argc, argv);

    //ros::NodeHandle n;
    auto node = rclcpp::Node::make_shared("listener");
     begin=steady_clock.now();

    //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    auto sub = node->create_subscription<std_msgs::msg::String>(
    "chatter", chatterCallback, rmw_qos_profile_default);

    //ros::spin();
    rclcpp::spin(node);

    return 0;
}





















