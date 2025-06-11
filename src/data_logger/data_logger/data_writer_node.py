import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, JointState
import os
from datetime import datetime
import yaml
import csv
import cv2
from cv_bridge import CvBridge

class DataWriterNode(Node):
    def __init__(self):
        super().__init__('data_writer_node')

        # Declare and get config file parameter (can be overridden by ros2 param)
        self.declare_parameter("config_file", "config/data_writer_config.yaml")
        self.config_file = self.get_parameter("config_file").get_parameter_value().string_value

        # Load config file (create default if not present)
        self.load_or_create_config(self.config_file)

        # Extract config parameters for easy access
        self.output_dir = self.config.get('output_dir', "/tmp/ros2_lerobot_dataset")
        self.max_episode_duration = self.config.get('max_episode_duration_s', 60)  # seconds
        self.max_frames_per_episode = self.config.get('max_frames_per_episode', 1000)
        self.topics = self.config.get('topics', {
            'rgb': '/camera/color/image_raw',
            'depth': '/camera/depth/image_raw',
            'joint_states': '/joint_states'
        })

        # Prepare output directories
        os.makedirs(self.output_dir, exist_ok=True)
        self.create_root_config()

        # Find next episode index and create folders
        self.episode_index = self.find_next_episode_index()
        self.create_episode_folders()

        # CvBridge for image conversion
        self.bridge = CvBridge()

        # Initialize counters and timers
        self.start_time = datetime.now()
        self.frame_count = 0

        # Open joint CSV file
        self.joint_csv_file = open(os.path.join(self.state_dir, 'joint_states.csv'), 'w', newline='')
        self.joint_csv_writer = None

        # Initialize meta info
        self.meta = {
            'episode_index': self.episode_index,
            'start_time': self.start_time.isoformat(),
            'rgb_images': 0,
            'depth_images': 0,
            'joint_state_msgs': 0
        }

        # Subscriptions
        self.color_sub = self.create_subscription(Image, self.topics['rgb'], self.color_callback, 10)
        self.depth_sub = self.create_subscription(Image, self.topics['depth'], self.depth_callback, 10)
        self.joint_sub = self.create_subscription(JointState, self.topics['joint_states'], self.joint_callback, 10)

        # Timer to check episode duration/frame count every second
        self.timer = self.create_timer(1.0, self.timer_callback)

        self.get_logger().info(f"DataWriterNode started. Recording to {self.output_dir}")

    def load_or_create_config(self, filepath):
        if not os.path.exists(filepath):
            self.get_logger().info(f"Config file {filepath} not found. Creating default config.")
            default_config = {
                'output_dir': '/tmp/ros2_lerobot_dataset',
                'max_episode_duration_s': 60,
                'max_frames_per_episode': 1000,
                'topics': {
                    'rgb': '/camera/color/image_raw',
                    'depth': '/camera/depth/image_raw',
                    'joint_states': '/joint_states'
                }
            }
            os.makedirs(os.path.dirname(filepath), exist_ok=True)
            with open(filepath, 'w') as f:
                yaml.dump(default_config, f)
            self.config = default_config
        else:
            with open(filepath, 'r') as f:
                self.config = yaml.safe_load(f)
            self.get_logger().info(f"Loaded config from {filepath}")

    def create_root_config(self):
        config_dir = os.path.join(self.output_dir, 'config')
        if not os.path.exists(config_dir):
            os.makedirs(config_dir)
        robot_config_path = os.path.join(config_dir, 'robot_description.yaml')
        if not os.path.exists(robot_config_path):
            sample_config = {
                'robot_name': 'my_robot',
                'description': 'Sample robot description for LeRobot dataset format',
                'joints': ['joint1', 'joint2', 'joint3'],
            }
            with open(robot_config_path, 'w') as f:
                yaml.dump(sample_config, f)
            self.get_logger().info(f"Created root robot_description.yaml at {robot_config_path}")

    def find_next_episode_index(self):
        episodes = [d for d in os.listdir(self.output_dir) if d.startswith('episode_')]
        indices = []
        for ep in episodes:
            try:
                indices.append(int(ep.split('_')[1]))
            except Exception:
                pass
        if indices:
            return max(indices) + 1
        else:
            return 1

    def create_episode_folders(self):
        self.episode_dir = os.path.join(self.output_dir, f'episode_{self.episode_index:06d}')
        self.rgb_dir = os.path.join(self.episode_dir, 'rgb')
        self.depth_dir = os.path.join(self.episode_dir, 'depth')
        self.state_dir = os.path.join(self.episode_dir, 'state')

        os.makedirs(self.rgb_dir, exist_ok=True)
        os.makedirs(self.depth_dir, exist_ok=True)
        os.makedirs(self.state_dir, exist_ok=True)
        self.get_logger().info(f"Created episode folders at {self.episode_dir}")

    def timer_callback(self):
        elapsed_time = (datetime.now() - self.start_time).total_seconds()
        if elapsed_time >= self.max_episode_duration or self.frame_count >= self.max_frames_per_episode:
            self.get_logger().info(f"Episode {self.episode_index} complete: duration={elapsed_time:.1f}s, frames={self.frame_count}")
            self.finish_episode()
            self.episode_index += 1
            self.create_episode_folders()
            self.start_time = datetime.now()
            self.frame_count = 0
            self.meta = {
                'episode_index': self.episode_index,
                'start_time': self.start_time.isoformat(),
                'rgb_images': 0,
                'depth_images': 0,
                'joint_state_msgs': 0
            }
            # Reopen joint CSV file for new episode
            if self.joint_csv_file:
                self.joint_csv_file.close()
            self.joint_csv_file = open(os.path.join(self.state_dir, 'joint_states.csv'), 'w', newline='')
            self.joint_csv_writer = None
            self.get_logger().info(f"Started new episode {self.episode_index}")

    def finish_episode(self):
        self.meta['end_time'] = datetime.now().isoformat()
        meta_path = os.path.join(self.episode_dir, 'meta.yaml')
        with open(meta_path, 'w') as f:
            yaml.dump(self.meta, f)
        if self.joint_csv_file:
            self.joint_csv_file.close()

    def color_callback(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            timestamp = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            filename = f"{timestamp:.9f}.png"
            filepath = os.path.join(self.rgb_dir, filename)
            cv2.imwrite(filepath, cv_image)
            self.meta['rgb_images'] += 1
            self.frame_count += 1
            self.get_logger().debug(f"Saved RGB image {filepath}")
        except Exception as e:
            self.get_logger().error(f"Failed to save RGB image: {str(e)}")

    def depth_callback(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            timestamp = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            filename = f"{timestamp:.9f}.png"
            filepath = os.path.join(self.depth_dir, filename)
            cv2.imwrite(filepath, cv_image)
            self.meta['depth_images'] += 1
            self.frame_count += 1
            self.get_logger().debug(f"Saved Depth image {filepath}")
        except Exception as e:
            self.get_logger().error(f"Failed to save Depth image: {str(e)}")

    def joint_callback(self, msg: JointState):
        try:
            if self.joint_csv_writer is None:
                header = ['timestamp'] + list(msg.name)
                self.joint_csv_writer = csv.writer(self.joint_csv_file)
                self.joint_csv_writer.writerow(header)

            timestamp = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            row = [timestamp] + list(msg.position)
            self.joint_csv_writer.writerow(row)
            self.joint_csv_file.flush()
            self.meta['joint_state_msgs'] += 1
            self.get_logger().debug(f"Logged joint state at {timestamp}")
        except Exception as e:
            self.get_logger().error(f"Failed to log joint state: {str(e)}")

def main(args=None):
    rclpy.init(args=args)
    node = DataWriterNode()
    rclpy.spin(node)
    node.finish_episode()  # Save meta on shutdown
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
