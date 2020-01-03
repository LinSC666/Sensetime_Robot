#include <ros/ros.h>
#include <ros/duration.h>
#include<ros/time.h>

int main( int argc, char **argv )
{

  ros::init( argc, argv, "example1" );
  ros::NodeHandle n;

  ros::Time begin=ros::Time::now();   //获取当前时间
   int task_nbr;
   ros::Duration total_msec;     // 定义一个时间点
   float msec;

   //***************************************************//
   //测试任务：打印一百万条指令所花费时间
    for (task_nbr = 0; task_nbr < 10000000; task_nbr++) {

          std::cout << "ROS_linsc_effiency_test!!!..." << std::endl;
    }
   //***************************************************//
  ros::Time end=ros::Time::now();   //获取结束时间
  total_msec=end -begin;
  msec=1000*(total_msec.toSec());

   printf("\nTotal elapsed time: %.2f msec\n",msec);
}

