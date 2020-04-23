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

//rclcpp::Duration total_msec;     // 定义一个时间点
float msec;

void chatterCallback(const std_msgs::msg::String::SharedPtr msg)
{
  std::cout <<"D3cpp_sub heard D2cpp_pub!!! " << std::endl;

}

int main(int argc, char * argv[])
{
    //ros::init(argc, argv, "listener");
    rclcpp::init(argc, argv);

    //ros::NodeHandle n;
    auto node = rclcpp::Node::make_shared("D3cpp");

    //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    auto sub = node->create_subscription<std_msgs::msg::String>(
    "D2cpp_pub", chatterCallback, rmw_qos_profile_default);

    //ros::spin();
    rclcpp::spin(node);

    return 0;
}





















