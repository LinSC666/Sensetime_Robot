#!/usr/bin/env python

import os
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge
import time

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')
        self.pub= self.create_publisher(Image, 'image_source/image_raw',10)
        width =980
        height =720
        frame_rate =10
        source_file = "/root/ros2_ws/ros_ws/src/image_source/lawn.mp4"
       
	# load image
        if os.path.isabs(source_file):
            filepath = source_file
        else:
            filepath = os.path.join(os.getcwd(), source_file)
            if not os.path.exists(filepath):
                filepath = os.path.join(os.path.dirname(os.path.abspath(__file__)), source_file)

        cap = cv2.VideoCapture(filepath)
 
   	# Check if video opened successfully
        if (cap.isOpened()== False): 
            print("Error opening video stream or file")
  
        # reduce frame rate to set frame rate
        fps = cap.get(cv2.CAP_PROP_FPS)
        fps_sample = round(fps / frame_rate)
  
        frame_id = 0
        frame_counter = 0
        #rate = rclpy.timer.Rate(frame_rate)
        bridge = CvBridge()
        #rospy.sleep(1)
        time.sleep(1) 

        while(cap.isOpened()):
            print("linsc6666")
            # Capture frame-by-frame and loop after reaching last frame
            ret, im = cap.read()

            frame_counter += 1
            # If the last frame is reached, reset the capture and the frame_counter
       	    if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
                frame_counter = 0
                cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

            # sample at set frames rate
            if frame_counter % fps_sample != 0:
                continue

            if ret == True:
                h, w = im.shape[:2]
 
                if h != height or w != width:
                    im = cv2.resize(im, (width, height))

                msg = bridge.cv2_to_imgmsg(im, encoding="bgr8")

                # publish message
                msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                msg.header.frame_id = str(frame_id)
                frame_id += 1
                self.pub.publish(msg)
                time.sleep(1/frame_rate)
            else:
                break
        cap.release()


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
