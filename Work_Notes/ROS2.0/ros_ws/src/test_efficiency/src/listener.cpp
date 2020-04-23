
#include "ros/ros.h"
#include "std_msgs/String.h"
#include<ros/time.h>

long long int num=0;
ros::Time begin;
ros::Time end;
ros::Duration total_msec;     // 定义一个时间点
float msec;

// 接收到订阅的消息后，会进入消息回调函数
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    // 将接收到的消息打印出来
   // ROS_INFO("I heard: [%s]", msg->data.c_str());
std::cout <<num<<std::endl;
    num++;
    if(num==1000000)
   {
   std::cout << "start_ZMQ_linsc_effiency_test!!!..." << std::endl;
   end=ros::Time::now();   //获取结束时间
   total_msec=end -begin;
   msec=1000*(total_msec.toSec());

   printf("\nTotal elapsed time: %.2f msec\n",msec);
	
   }
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "listener");

    // 创建节点句柄
    ros::NodeHandle n;

     begin=ros::Time::now();   //获取当前时间

    // 创建一个Subscriber，订阅名为chatter的topic，注册回调函数chatterCallback
    ros::Subscriber sub = n.subscribe("chatter", 16, chatterCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}
