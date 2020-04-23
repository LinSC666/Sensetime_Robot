#include "gos.h"
#include "gos.cpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <opencv2/opencv.hpp>
#include "velocity_msg_.pb.h"
#include "odom_msg_.pb.h"


//***********************************//
//Linux shareMemory communication
//Publish
//LinSC
//2020/2/29
//***********************************//

using namespace std;
using namespace cv;
using namespace gos;


//template<class T>
void cmdVelCallback(const demo::twist receive_msg)
{
    // 将接收到的消息打印出来
   // cout<<"chatterCallback!!!"<<a<<endl;
	cout<<"callback_linear_x: "<< receive_msg.linear_x()<<endl;
    cout<<"callback_angular_z: "<< receive_msg.angular_z()<< "\n\n"<<endl;
}


int main()
{
    gos::Subscriber<demo::twist> shm_vel_pub;
    gos::Publisher shm_odom_pub;
    //gos::Subscriber n1;
   // gos::test out;
    shm_odom_pub.advertiser<demo::odometry>("topic_2","/home/gophield/linsc_shm/3msg_pic_proto_demo/gos_config.json");
    demo::odometry shm_odom_msg;
    demo::odometry deserialize_msg;
    double num=0.0;
    while(1)
    {
    	shm_vel_pub.subscribe("topic_1","gos.sub.node1.topic_1.sub1",cmdVelCallback);
    	//n1.subscribe<const demo::msg>("topic_2","gos.sub.node2.topic_2.sub1",chatterCallback);
    //	out.print<const char*>("abcefgh");
        num+=1.00010000000000000100000000000001;
       // cout<<"value:"<<num<<endl;
        printf("%.32f\n",num);
        shm_odom_msg.set_pose_pose_position_x(num);
        shm_odom_msg.set_pose_pose_position_y(num);
        shm_odom_msg.set_pose_pose_orientation_x(num);
        shm_odom_msg.set_pose_pose_orientation_y(num);
        shm_odom_msg.set_pose_pose_orientation_z(num);
        shm_odom_msg.set_pose_pose_orientation_w(num);
      /*  string msg_v_;
        shm_odom_msg.SerializeToString(&msg_v_);
        deserialize_msg.ParseFromString(msg_v_);
        cout<<"***********************************************"<<endl;
        printf("%.13f\n",deserialize_msg.pose_pose_position_x());
        printf("%.13f\n",deserialize_msg.pose_pose_position_y());
        printf("%.13f\n",deserialize_msg.pose_pose_orientation_x());
        printf("%.13f\n",deserialize_msg.pose_pose_orientation_y());
        printf("%.13f\n",deserialize_msg.pose_pose_orientation_z());
        printf("%.13f\n",deserialize_msg.pose_pose_orientation_w());
        cout<<"------------------------------------------------"<<endl;
     */
        shm_odom_pub.publish(shm_odom_msg);        
    	//cout<<"add: "<<c<<endl;
    	//usleep(10000);
    }
    
}


















