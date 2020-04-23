#include <fstream>
#include <iostream>
#include <iomanip>
#include <unistd.h>

#include "oap_net.h"
#include "base_engine.h"
#include "common.h"
#include "get_image.h"

#include "ros/ros.h"
#include "am_msgs/DetectionResult.h"
#include "am_msgs/Object.h"

int main(int argc, char** argv) {

	ros::init(argc, argv, "detection_node");
  	ros::NodeHandle nh("~");
	ros::Publisher publisher = nh.advertise<am_msgs::DetectionResult>("/detection_result", 1);
	am_msgs::DetectionResult pub_msg;
	pub_msg.header.frame_id = "/map";

	std::string engine_file; 
	nh.getParam("engine_file", engine_file);
  	ROS_INFO("engine_file = %s", engine_file.c_str());
	std::string imwrite_path; 
	nh.getParam("imwrite_path", imwrite_path);
  	ROS_INFO("imwrite_path = %s", imwrite_path.c_str());
	int is_visulized; 
	nh.getParam("is_visulized", is_visulized);
  	ROS_INFO("is_visulized = %d", is_visulized);

	TRTCommon::PrintTRTVersion();
	auto OAP_Engine = BaseEngine(NULL, NULL, engine_file);
	auto OAP_net = OAPNet(OAP_Engine);

	MynteyeLeftCamera camera;
	cv::Mat image;
	cv::Mat image_ori;

    cout.setf(ios::fixed);
	cout << fixed << setprecision(3);

	cout << "detection start!\n" << endl;
	int count = 0;
	while(ros::ok()) {
		camera.wattForStream();
	    char key = static_cast<char>(cv::waitKey(1));

		bool state = camera.getUndistortedImage(image);
		image_ori = image;
		if(state) { 
			std::vector<RealWorldCoordinate> oap_output = OAP_net.Run(image,"",OAP_Engine);

			// load ROS message
			pub_msg.header.stamp = ros::Time::now();
			cout << "target number is:" << oap_output.size() << endl;
			if(!oap_output.empty()) { 
				pub_msg.objects.clear(); //clear();
				am_msgs::Object object;
				for(int i = 0; i < oap_output.size(); i++) {
					object.object_index = i;
					double x = (oap_output[i].bottom_left.x+oap_output[i].bottom_right.x)/2;
					double y = (oap_output[i].bottom_left.y+oap_output[i].bottom_right.y)/2;
					cout << "left: " << oap_output[i].bottom_left.x << ", " << oap_output[i].bottom_left.y;
				        cout << ";\tright: " << oap_output[i].bottom_right.x << ", " << oap_output[i].bottom_right.y;
                                        cout << ";\tcenter: " << x << "," << y  << endl;
					object.position.x = x;
					object.position.y = y;
					pub_msg.objects.push_back(object);
				}
				publisher.publish(pub_msg); // publish
			}
			std::cout << "count = " << count++ <<std::endl << std::endl;
			

			if(is_visulized) {
				cv::imshow("detection result", image);
				//std::cout << "image's size = " << image.cols << "X" << image.rows << std::endl << std::endl;
			}
		}
    
		if (key == 27 || key == 'q' || key == 'Q') {  // ESC/Q
			break;
		}
		else if (key == 's' || key == 'S') { 
			cv::imwrite(imwrite_path + std::to_string(count) + "_in.png", image_ori);
			cv::imwrite(imwrite_path + std::to_string(count) + "_out.png", image);
		}

		
	}







	// while(ros::ok()) {
	// 	;
	// }
	

}
