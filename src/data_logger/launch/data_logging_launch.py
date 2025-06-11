from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir
import os

def generate_launch_description():
    # Path to the RealSense launch file (provided by realsense2_camera package)
    realsense_launch_path = os.path.join(
        get_package_share_directory('realsense2_camera'),
        'launch',
        'rs_camera.launch.py'
    )

    return LaunchDescription([

        # Launch Intel RealSense Camera Node
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(realsense_launch_path),
            launch_arguments={
                'enable_color': 'true',
                'enable_depth': 'false',
                'pointcloud.enable': 'false',
            }.items(),
        ),

        # Data Writer Node
        Node(
            package='data_logger',
            executable='data_writer_node',
            name='data_writer_node',
            output='screen',
            parameters=[
                {'base_output_dir': '/tmp/data_log'},
            ]
        ),

        # Image Saver Node
        Node(
            package='data_logger',
            executable='image_saver_node',
            name='image_saver_node',
            output='screen',
            parameters=[
                {'save_raw_images': True},
                {'camera_topic': '/camera/color/image_raw'},
            ],
            remappings=[
                ('/camera/image_raw', '/camera/color/image_raw'),
                ('/writer_node/output_dir', '/writer_node/output_dir'),
                ('/writer_node/write_step_str', '/writer_node/write_step_str'),
            ],
        ),

        # Robot Saver Node
        Node(
            package='data_logger',
            executable='robot_saver_node',
            name='robot_saver_node',
            output='screen',
            parameters=[
                {'robot_out_folder': '/tmp/ros2_robot'},
            ],
            remappings=[
                ('/joint_states', '/joint_states'),
                ('/wrench', '/wrench'),
                ('/cartesian_pose', '/cartesian_pose'),
                ('/ios_state', '/ios_state'),
                ('/writer_node/output_dir', '/writer_node/output_dir'),
                ('/writer_node/write_step_str', '/writer_node/write_step_str'),
            ],
        ),
    ])
