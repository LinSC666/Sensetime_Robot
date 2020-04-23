gnome-terminal --window -e  'bash -c "source ~/catkin_ws/devel/setup.bash;roslaunch ca_driver create_2.launch;exec bash "' \
--tab -e 'bash -c "sleep 7;source ~/catkin_ws/devel/setup.bash;roslaunch ca_tools joy_teleop.launch; exec bash"' \
--tab -e 'bash -c "sleep 5; source ~/catkin_ws/devel/setup.bash; roslaunch rplidar_ros rplidar.launch; exec bash"' \
--tab -e 'bash -c "sleep 10;source /home/gophield/cartographer_ros/src/ros/devel/setup.bash; roslaunch cartographer_ros demo_revo_lds.launch; exec bash"' \

