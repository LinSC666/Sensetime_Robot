#!/usr/bin/env python

import socket, traceback
import xml.etree.ElementTree
import math

import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Pose, Vector3
from sensor_msgs.msg import Imu, MagneticField

def PublishData():
    pose_pub = rospy.Publisher('phone_pose', Pose, queue_size=10)
    imu_pub = rospy.Publisher('phone_imu', Imu, queue_size=10)
    mag_pub = rospy.Publisher('phone_mag', MagneticField, queue_size=10)
    rospy.init_node('phone_sensors', anonymous=True)

    host = ''
    port = 50000
    
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    s.bind((host, port))
    
    print("Success binding")
    while not rospy.is_shutdown():
        message, address = s.recvfrom(4096)
        message_str = message.decode("utf-8")
        try:
            message_str = message_str.replace("<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>", "<?xml version='1.0' encoding='UTF-8' standalone='yes' ?><Sensors>")
            message_str = message_str.replace("</TimeStamp>", "</TimeStamp></Sensors>")
            # print(message_str) 
            sensors_node = xml.etree.ElementTree.fromstring(message_str)

            imu = Imu()
            
            for accel_node in sensors_node.iter('Accelerometer'):
                accel_x = float(accel_node.find('Accelerometer1').text)
                accel_y = float(accel_node.find('Accelerometer2').text)
                accel_z = float(accel_node.find('Accelerometer3').text)
                imu.linear_acceleration = Vector3(accel_x, accel_y, accel_z)
                imu.linear_acceleration_covariance = [0.01, 0, 0, 0, 0.01, 0, 0, 0, 0.01]

            for gyro_node in sensors_node.iter('Gyroscope'):
                gyro_x = float(gyro_node.find('Gyroscope1').text)
                gyro_y = float(gyro_node.find('Gyroscope2').text)
                gyro_z = float(gyro_node.find('Gyroscope3').text)            
                imu.angular_velocity = Vector3(gyro_x, gyro_y, gyro_z)
                imu.angular_velocity_covariance = [0.0025, 0, 0, 0, 0.0025, 0, 0, 0, 0.0025]

            for mag_node in sensors_node.iter('Magnetometer'):
                mag_x = float(mag_node.find('Magnetometer1').text)
                mag_y = float(mag_node.find('Magnetometer2').text)
                mag_z = float(mag_node.find('Magnetometer3').text)

                mag = MagneticField()
                mag.header.frame_id = 'base_link'
                mag.header.stamp = rospy.Time.now()
                mag.magnetic_field = Vector3(mag_x, mag_y, mag_z)
                mag.magnetic_field_covariance = [0, 0, 0, 0, 0, 0, 0, 0, 0]
                mag_pub.publish(mag)

            for linear_accel_node in sensors_node.iter('LinearAcceleration'):
                linear_accel_x = float(linear_accel_node.find('LinearAcceleration1').text)
                linear_accel_y = float(linear_accel_node.find('LinearAcceleration2').text)
                linear_accel_z = float(linear_accel_node.find('LinearAcceleration3').text)

            imu.orientation_covariance = [-1, 0, 0, 0, 0, 0, 0, 0, 0]
            imu.header.frame_id = 'base_link'
            imu.header.stamp = rospy.Time.now()

            imu_pub.publish(imu)                

            for rotation_vector_node in sensors_node.iter('RotationVector'):
                x = float(rotation_vector_node.find('RotationVector1').text)
                y = float(rotation_vector_node.find('RotationVector2').text)
                z = float(rotation_vector_node.find('RotationVector3').text)
                w = math.sqrt(1.0 - x*x - y*y - z*z)

                pose = Pose()
                pose.position.x = 0
                pose.position.y = 0
                pose.position.z = 0

                pose.orientation.x = x
                pose.orientation.y = y
                pose.orientation.z = z
                pose.orientation.w = w
                
                pose_pub.publish(pose)

                # print(x," ", y, " ", z, " ", w)

                r = math.atan2(2*(w*x+y*z),1-2*(x*x+y*y))
                p = math.asin(2*(w*y-z*x))
                y = math.atan2(2*(w*z+x*y),1-2*(z*z+y*y))

                angleR = r*180/math.pi
                angleP = p*180/math.pi
                angleY = y*180/math.pi

                # print("(", angleR, " ", angleP, " ", angleY, " )")
                rospy.loginfo("(%f, %f, %f)", angleR, angleP, angleY)
            
        except:
            print("parse error")

if __name__ == '__main__':
    try:
        PublishData()
    except rospy.ROSInterruptException:
        pass