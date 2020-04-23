#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/clock.hpp"

//*************************//
//By linsc
//*************************//


rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_e;
auto pub_msg = std::make_shared<std_msgs::msg::String>();

//rclcpp::Duration total_msec;     // 定义一个时间点
float msec;

void chatterCallback(const std_msgs::msg::String::SharedPtr msg)
{
  std::cout << "L3:g [" << msg->data << "]" << std::endl;

}

int main(int argc, char * argv[])
{
    //ros::init(argc, argv, "listener");
    rclcpp::init(argc, argv);

    //ros::NodeHandle n;
    auto node = rclcpp::Node::make_shared("l3");

    //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    auto sub = node->create_subscription<std_msgs::msg::String>(
    "pub_e", chatterCallback, rmw_qos_profile_default);

  
   // auto msg = std::make_shared<std_msgs::msg::String>();
   // auto i = 1;

    rclcpp::spin(node);

    return 0;
}





















