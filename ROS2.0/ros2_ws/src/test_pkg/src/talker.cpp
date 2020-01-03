#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


//*************************//
//By linsc
//*************************//


long long int  num=0;

int main(int argc, char * argv[])
{

    rclcpp::init(argc, argv);
   
    auto node = rclcpp::Node::make_shared("talker");

    rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_default;
    
    custom_qos_profile.depth = 10;

    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    auto chatter_pub = node->create_publisher<std_msgs::msg::String>("chatter", custom_qos_profile);

  
    auto msg = std::make_shared<std_msgs::msg::String>();
   // auto i = 1;

    while (rclcpp::ok()) 
    {
       msg->data = "hello world";
       chatter_pub->publish(msg);
       num++;
       printf("%lld\n",num);
       
       rclcpp::spin_some(node);
    }

    return 0;
}
