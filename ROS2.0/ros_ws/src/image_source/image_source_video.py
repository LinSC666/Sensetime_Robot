#!/usr/bin/env python

import os
import rospy
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge

def image_source_video():
    # initialize
    rospy.init_node('image_source_video', anonymous=True)
    pub = rospy.Publisher('image_source/image_raw', Image, queue_size=10)

    # load parameters
    width = int(rospy.get_param('~width', '1920'))
    height = int(rospy.get_param('~height', '1080'))
    frame_rate = int(rospy.get_param('~frame_rate', '10'))
    source_file = "/root/ros2_ws/ros_ws/src/image_source/lawn.mp4"

    rospy.loginfo("Param: image width = %d", width)
    rospy.loginfo("Param: image height = %d", height)
    rospy.loginfo("Param: frame rate = %d", frame_rate)

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
    rospy.loginfo("Frame sampling multiplier = %d", fps_sample)

    frame_id = 0
    frame_counter = 0
    rate = rospy.Rate(frame_rate)
    bridge = CvBridge()
    rospy.sleep(1)
    while(not rospy.is_shutdown() and cap.isOpened()):
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
            msg.header.stamp = rospy.Time.now()
            msg.header.frame_id = str(frame_id)
            frame_id += 1
            pub.publish(msg)
            rate.sleep()
        else:
            break

    # When everything done, release the video capture object
    cap.release()

if __name__ == '__main__':
    try:
        image_source_video()
    except rospy.ROSInterruptException:
        pass
