gnome-terminal --window -e 'bash -c "source ~/catkin_ws/devel/setup.bash;roslaunch ca_driver create_2.launch;exec bash "' \
--tab -e 'bash -c "sleep 7;source ~/catkin_ws/devel/setup.bash;roslaunch ca_tools joy_teleop.launch; exec bash"' \
--tab -e 'bash -c "sleep 5; cd /home/gophield/catkin_ws/src/rplidar_ros/launch; source ~/catkin_ws/devel/setup.bash;roslaunch my_launch.launch; exec bash"' \
--tab -e 'bash -c "sleep 10; cd /home/gophield/catkin_ws/src/rplidar_ros/launch;roslaunch rp-gmapping.launch; exec bash"' \

