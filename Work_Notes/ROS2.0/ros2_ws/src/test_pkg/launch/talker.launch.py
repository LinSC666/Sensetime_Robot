from launch import LaunchDescription
import launch_ros.actions
 
 
def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
           
            package='test_pkg', node_executable='image_source_video', output='screen'),

    ])
