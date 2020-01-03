#include <ros/ros.h>

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>
#include <atomic>

#include "sensor_msgs/Image.h"

sensor_msgs::Image image_test;

std::atomic_bool is_tested;

int flag_num=0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    image_test=*msg;
   // ROS_INFO("111111111111111111111111111\n");
    flag_num++;

    if(flag_num > 3)
    {
       is_tested = true;
       flag_num=0;
    }

}

TEST(ImageTest,SizeTest)
{
    try{
    ros::NodeHandle nh;
    ros::Subscriber ImageSub = nh.subscribe ("image_source/image_raw", 1, &imageCallback);
   // ROS_INFO("666666666666666666666666666\n");

    is_tested = false;

    while(!is_tested) 
    {//这里确保了rostest只需回调和执行一次
     ros::spinOnce();//这里确保了rostest只需回调和执行一次
    // ros::spin();//如何用spin()的话，其实也对，但只会一直在等待，停住,而没有打印结果!要按ctrl+c才能退出，打印最终结果!
    }
   
    EXPECT_GT(std::stoi(image_test.header.frame_id),1);

    EXPECT_EQ(1280,image_test.width);
    EXPECT_EQ(720,image_test.height);
  }

  
  catch(...){
    ADD_FAILURE()<<"Uncaught exception : " <<"This is OK on Ubuntu16.04!";
  }
  // EXPECT_EQ(is_tested, true);

}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  ros::init(argc, argv, "image_test");

  //ros::Time::init();

  return RUN_ALL_TESTS();
}