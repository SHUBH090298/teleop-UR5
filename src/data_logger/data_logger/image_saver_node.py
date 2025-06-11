#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
import os
import pickle

class ImageSaverNode(Node):
    def __init__(self):
        super().__init__('image_saver_node')
        self.bridge = CvBridge()

        # Store current episode path and step string
        self.current_output_dir = None
        self.current_step_str = None

        # Subscribers
        self.create_subscription(Image, '/camera/color/image_raw', self.callback_color, 10)
        self.create_subscription(Image, '/camera/infra1/image_raw', self.callback_ir1, 10)
        self.create_subscription(Image, '/camera/infra2/image_raw', self.callback_ir2, 10)

        self.create_subscription(CameraInfo, '/camera/color/camera_info', self.callback_color_info, 10)
        self.create_subscription(CameraInfo, '/camera/infra1/camera_info', self.callback_ir1_info, 10)
        self.create_subscription(CameraInfo, '/camera/infra2/camera_info', self.callback_ir2_info, 10)

        self.create_subscription(String, '/writer_node/output_dir', self.callback_output_dir, 10)
        self.create_subscription(String, '/writer_node/write_step_str', self.callback_write_step, 10)

        # Cache for camera_info
        self.camera_info_cache = {'color': None, 'ir1': None, 'ir2': None}
        self.saved_camera_info_flags = {'color': False, 'ir1': False, 'ir2': False}

    def callback_output_dir(self, msg):
        self.current_output_dir = msg.data
        self.get_logger().info(f"Updated episode output directory to: {self.current_output_dir}")

        # Reset camera_info save flags for new episode
        self.saved_camera_info_flags = {'color': False, 'ir1': False, 'ir2': False}

        # Ensure necessary subfolders exist
        os.makedirs(os.path.join(self.current_output_dir, 'rgb'), exist_ok=True)
        os.makedirs(os.path.join(self.current_output_dir, 'ir1'), exist_ok=True)
        os.makedirs(os.path.join(self.current_output_dir, 'ir2'), exist_ok=True)
        os.makedirs(os.path.join(self.current_output_dir, 'camera_info'), exist_ok=True)

    def callback_write_step(self, msg):
        self.current_step_str = msg.data

    def save_image(self, image_msg, cam_type):
        if not self.current_output_dir or not self.current_step_str:
            return

        try:
            cv_image = self.bridge.imgmsg_to_cv2(image_msg, desired_encoding='passthrough')
            filename = os.path.join(self.current_output_dir, cam_type, f"{self.current_step_str}.png")
            cv2.imwrite(filename, cv_image)
            self.get_logger().info(f"[{cam_type}] Saved image: {filename}")
        except Exception as e:
            self.get_logger().error(f"Failed to save {cam_type} image: {str(e)}")

    def save_camera_info(self, info_msg, cam_type):
        if self.saved_camera_info_flags[cam_type]:
            return  # Save only once per episode

        self.camera_info_cache[cam_type] = info_msg
        filepath = os.path.join(self.current_output_dir, 'camera_info', f'{cam_type}_info.pkl')
        try:
            with open(filepath, 'wb') as f:
                pickle.dump(info_msg, f)
            self.saved_camera_info_flags[cam_type] = True
            self.get_logger().info(f"Saved {cam_type} camera_info to {filepath}")
        except Exception as e:
            self.get_logger().error(f"Failed to save {cam_type} camera_info: {str(e)}")

    # Image callbacks
    def callback_color(self, msg): self.save_image(msg, 'rgb')
    def callback_ir1(self, msg): self.save_image(msg, 'ir1')
    def callback_ir2(self, msg): self.save_image(msg, 'ir2')

    # CameraInfo callbacks
    def callback_color_info(self, msg): self.save_camera_info(msg, 'color')
    def callback_ir1_info(self, msg): self.save_camera_info(msg, 'ir1')
    def callback_ir2_info(self, msg): self.save_camera_info(msg, 'ir2')


def main(args=None):
    rclpy.init(args=args)
    node = ImageSaverNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
