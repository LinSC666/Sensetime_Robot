from launch import LaunchDescription

import launch_ros.actions

def generate_launch_description():

    return LaunchDescription([

        launch_ros.actions.Node(
            package='test_pkg',
            node_executable='image_source_video.py',
            node_namespace='image_source_video'
          #  node_namespace= "ros2", package='test_pkg', node_executable='talker', output='screen'
       ),

        launch_ros.actions.Node(

           # node_namespace= "ros2", package='test_pkg', node_executable='listener', output='screen'
       ),

    ])


