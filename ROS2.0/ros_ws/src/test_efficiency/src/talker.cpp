#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"

long long int num=0;

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "talker");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为chatter的topic，消息类型为std_msgs::String
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 16);

    // 设置循环的频率
  //  ros::Rate loop_rate(10);

    //int count = 0;
    while (ros::ok())
    {
        // 初始化std_msgs::String类型的消息
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world" ;
        msg.data = ss.str();

        // 发布消息
     //   ROS_INFO("%s", msg.data.c_str());
    //printf("%s\n", msg.data.c_str());

        chatter_pub.publish(msg);
      num++;
     printf("%lld\n",num);

        // 循环等待回调函数
        ros::spinOnce();

        // 按照循环频率延时
       // loop_rate.sleep();
       // ++count;
    }

    return 0;
}