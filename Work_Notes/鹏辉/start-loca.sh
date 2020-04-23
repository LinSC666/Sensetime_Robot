gnome-terminal --window -e 'bash -c "source ~/catkin_ws/devel/setup.bash;roslaunch ca_driver create_2.launch;exec bash "' \
--tab -e 'bash -c "sleep 7;source ~/catkin_ws/devel/setup.bash;roslaunch ca_tools joy_teleop.launch; exec bash"' \
--tab -e 'bash -c "sleep 10; source ~/catkin_ws/devel/setup.bash; cd /home/gophield/catkin_ws/src/rplidar_ros/launch;roslaunch agv.launch; exec bash"' \

