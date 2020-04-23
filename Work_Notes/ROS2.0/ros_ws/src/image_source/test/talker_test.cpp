#include <ros/ros.h>

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>

#include "std_msgs/String.h"
#include <atomic>

std_msgs::String talker_test;
std::atomic_bool is_tested;

void imageCallback(const std_msgs::String::ConstPtr& msg)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  talker_test=*msg;
    is_tested = true;
}

    
TEST(ImageTest,SizeTest)
{
   
  ros::NodeHandle nh;
  ros::Subscriber ImageSub = nh.subscribe ("chatter", 1, &imageCallback);
  
  is_tested = false;

while(!is_tested) {//这里确保了rostest只需回调和执行一次
   ros::spinOnce();//这里确保了rostest只需回调和执行一次
  // ros::spin();//如何用spin()的话，其实也对，但只会一直在等待，停住,而没有打印结果!要按ctrl+c才能退出，打印最终结果!
  }
 
  EXPECT_STREQ("hello world 10",talker_test.data.c_str());
 
  

}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  ros::init(argc, argv, "talker_test");
 
 // ros::Time::init();

 // ros::Duration(2.0).sleep();
 
  return RUN_ALL_TESTS();
}