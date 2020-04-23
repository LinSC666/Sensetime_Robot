#!/usr/bin/env python

import os
import rospy
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge

def image_source_dummy():
    # initialize
    rospy.init_node('image_source_dummy', anonymous=True)
    pub = rospy.Publisher('image_source/image_raw', Image, queue_size=10)

    # load parameters
    width = int(rospy.get_param('~width', '1920'))
    height = int(rospy.get_param('~height', '1080'))
    frame_rate = int(rospy.get_param('~frame_rate', '10'))
    source_file = rospy.get_param('~source_file', 'lawn.jpg')

    # load image
    if os.path.isabs(source_file):
        filepath = source_file
    else:
        filepath = os.path.join(os.getcwd(), source_file)
        if not os.path.exists(filepath):
            filepath = os.path.join(os.path.dirname(os.path.abspath(__file__)), source_file)
    im = cv2.imread(filepath, cv2.IMREAD_COLOR)
    h, w = im.shape[:2]

    if h != height or w != width:
        im = cv2.resize(im, (width, height))

    bridge = CvBridge()
    msg = bridge.cv2_to_imgmsg(im, encoding="bgr8")
    frame_id = 0

    rospy.sleep(1)

    # publish message
    rate = rospy.Rate(frame_rate)
    while not rospy.is_shutdown():
        msg.header.stamp = rospy.Time.now()
        msg.header.frame_id = str(frame_id)
        frame_id += 1
        pub.publish(msg)
        rate.sleep()


if __name__ == '__main__':
    try:
        image_source_dummy()
    except rospy.ROSInterruptException:
        pass
