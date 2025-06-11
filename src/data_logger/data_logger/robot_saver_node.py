import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import WrenchStamped, PoseStamped
from std_msgs.msg import String
from message_filters import ApproximateTimeSynchronizer, Subscriber
import os
import pandas as pd
from datetime import datetime

class RobotSaverNode(Node):
    def __init__(self):
        super().__init__('robot_saver_node')
        self.declare_parameter("robot_out_folder", "/tmp/ros2_robot")

        self.output_dir_ready = False
        self.write_step_str = None

        # Subscribers for control signals
        self.out_dir_sub = self.create_subscription(String, 'writer_node/output_dir', self.callback_out_dir, 10)
        self.write_step_sub = self.create_subscription(String, '/writer_node/write_step_str', self.callback_write_step, 10)

        # Message filter subscribers for syncing robot state
        self.joint_sub = Subscriber(self, JointState, '/joint_states')
        self.force_sub = Subscriber(self, WrenchStamped, '/wrench')
        self.cart_sub = Subscriber(self, PoseStamped, '/cartesian_pose')
        self.ios_sub = Subscriber(self, String, '/ios_state')

        self.ts = ApproximateTimeSynchronizer(
            [self.joint_sub, self.force_sub, self.cart_sub, self.ios_sub],
            queue_size=10,
            slop=0.1
        )
        self.ts.registerCallback(self.robot_state_callback)

        self.current_robot_data = None  # Holds the last synchronized data

    def callback_out_dir(self, msg):
        self.output_dir_glob = msg.data
        self.output_dir_ready = True
        self.get_logger().info(f"RobotSaverNode: Output directory set to {self.output_dir_glob}")

    def callback_write_step(self, msg):
        if not self.output_dir_ready or self.current_robot_data is None:
            self.get_logger().warn("Cannot write robot data: Output dir or robot state not ready.")
            return

        write_step_str = msg.data
        episode_path = os.path.join(self.output_dir_glob, write_step_str)
        os.makedirs(episode_path, exist_ok=True)

        joint_state, force_state, cart_state, ios_state = self.current_robot_data

        # Convert messages to dicts for easier saving
        joint_dict = {
            'time': self.get_clock().now().to_msg().sec + self.get_clock().now().to_msg().nanosec * 1e-9,
            'name': list(joint_state.name),
            'position': list(joint_state.position),
            'velocity': list(joint_state.velocity),
            'effort': list(joint_state.effort)
        }
        force_dict = {
            'time': force_state.header.stamp.sec + force_state.header.stamp.nanosec * 1e-9,
            'force_x': force_state.wrench.force.x,
            'force_y': force_state.wrench.force.y,
            'force_z': force_state.wrench.force.z,
            'torque_x': force_state.wrench.torque.x,
            'torque_y': force_state.wrench.torque.y,
            'torque_z': force_state.wrench.torque.z
        }
        cart_dict = {
            'time': cart_state.header.stamp.sec + cart_state.header.stamp.nanosec * 1e-9,
            'pos_x': cart_state.pose.position.x,
            'pos_y': cart_state.pose.position.y,
            'pos_z': cart_state.pose.position.z,
            'ori_x': cart_state.pose.orientation.x,
            'ori_y': cart_state.pose.orientation.y,
            'ori_z': cart_state.pose.orientation.z,
            'ori_w': cart_state.pose.orientation.w
        }
        ios_dict = {
            'time': self.get_clock().now().to_msg().sec + self.get_clock().now().to_msg().nanosec * 1e-9,
            'ios_state': ios_state.data
        }

        pd.DataFrame([joint_dict]).to_parquet(os.path.join(episode_path, "joint_states.parquet"), index=False)
        pd.DataFrame([force_dict]).to_parquet(os.path.join(episode_path, "force.parquet"), index=False)
        pd.DataFrame([cart_dict]).to_parquet(os.path.join(episode_path, "cartesian_pose.parquet"), index=False)
        pd.DataFrame([ios_dict]).to_parquet(os.path.join(episode_path, "ios_state.parquet"), index=False)

        self.get_logger().info(f"Saved robot state to {episode_path}")

    def robot_state_callback(self, joint_state, force_state, cart_state, ios_state):
        self.current_robot_data = (joint_state, force_state, cart_state, ios_state)

def main(args=None):
    rclpy.init(args=args)
    node = RobotSaverNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
