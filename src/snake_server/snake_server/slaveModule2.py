#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time

class Module_2_ServerNode(Node):
    def __init__(self):
        super().__init__("module_2_server_node")
        self.get_logger().info("module 2 server node has been started")

        self.master_subscriber = self.create_subscription(Twist, "master_module", self.masterCallback, 10)
        self.module_2_publisher = self.create_publisher(Twist, "module_2", 10)

        self.auxModule = Twist()
        self.auxModule.angular.z = 0.0
        self.auxModule.angular.y = 0.0

    def masterCallback(self, module: Twist):
        self.auxModule = module
        time.sleep(2) 
        self.module_2_publisher.publish(self.auxModule)       
        print(f"Module: {module}\n")

def main(args=None):
    rclpy.init(args=args)
    node = Module_2_ServerNode()
    rclpy.spin(node)
    rclpy.shutdown()