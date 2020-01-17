#!/bin/bash
echo "start!!!"
mycount=0
while(( $mycount <1200 ))
do
	source ~/ros2_ws/ROS2.0/ros2_ws/install/setup.bash 
	{
	  ros2 run py_pubsub image_source_video 
	}& #这个&代表后台运行！很重要！

	sleep 1s
	{
	  ros2 run test_pkg D2cpp
	}&

	sleep 1s
	{
	  ros2 run test_pkg D3cpp
	}&

	sleep 1s
	{
	  ros2 run test_pkg L1
	}&

	sleep 1s
	{
	  ros2 run test_pkg L3
	}&
        sleep 1s
	{
	  ros2 run test_pkg talker
	}&

	sleep 1s
	{
	  ros2 run test_pkg listener
	}&

	sleep 3s
	{ 
	  echo "hello!"
	   ps -ef | grep /image_source_video | grep -v grep | awk '{print $2}' | xargs sudo kill -9 
	   ps -ef | grep /D2cpp | grep -v grep | awk '{print $2}' | xargs sudo kill -9   
	   ps -ef | grep /D3cpp | grep -v grep | awk '{print $2}' | xargs sudo kill -9 
           ps -ef | grep /image_source_video | grep -v grep | awk '{print $2}' | xargs sudo kill -9 
	   ps -ef | grep /L1 | grep -v grep | awk '{print $2}' | xargs sudo kill -9   
	   ps -ef | grep /L3 | grep -v grep | awk '{print $2}' | xargs sudo kill -9 
           ps -ef | grep /talker | grep -v grep | awk '{print $2}' | xargs sudo kill -9   
	   ps -ef | grep /listener | grep -v grep | awk '{print $2}' | xargs sudo kill -9 
	}
      mycount=$mycount+1

done

