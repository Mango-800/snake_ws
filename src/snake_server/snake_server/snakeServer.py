#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class SnakeServerNode(Node):
    def __init__(self):
        super().__init__("snake_server_node")
        self.get_logger().info("snake server node has been started")

        self.module_subscriber = self.create_subscription(Twist, "snake_module", self.moduleCallback, 10)
        self.module_master_publisher = self.create_publisher(Twist, "module_master", 10)

        self.auxModule = Twist()

        self.messages_slave_1 = []
        self.messages_slave_2 = []
        self.messages_slave_3 = []
        self.delays = [2.0, 4.0, 6.0]
        self.create_timer(0.1, self.checkMessages)

    def moduleCallback(self, module: Twist):
        if module.linear.y == 0.0:
            module.linear.y = 1.0
            self.module_master_publisher.publish(module)

            if (self.auxModule.angular.z != module.angular.z) or (self.auxModule.angular.y != module.angular.y): 
                self.messages_slave_1.append((module, self.get_clock().now().to_msg().sec + self.delays[0]))   
                self.messages_slave_2.append((module, self.get_clock().now().to_msg().sec + self.delays[1]))   
                self.messages_slave_3.append((module, self.get_clock().now().to_msg().sec + self.delays[2]))   
            
        else:
            self.module_master_publisher.publish(module)
            self.get_logger().info(f"Module: {module}\n")

        self.auxModule = module

    def checkMessages(self):
        current_time = self.get_clock().now().to_msg().sec

        if self.messages_slave_1 and self.messages_slave_1[0][1] <= current_time:
            slave_1_msg, _ = self.messages_slave_1.pop(0)
            slave_1_msg.linear.y = 2.0
            self.publishSlaveMessage(slave_1_msg)
        if self.messages_slave_2 and self.messages_slave_2[0][1] <= current_time:
            slave_2_msg, _ = self.messages_slave_2.pop(0)
            slave_2_msg.linear.y = 3.0
            self.publishSlaveMessage(slave_2_msg)
    
    def publishSlaveMessage(self, slave_msg):
        self.module_master_publisher.publish(slave_msg)
        self.get_logger().info(f"Module: {int(slave_msg.linear.y)}")
        self.get_logger().info(f"Speed: {int(slave_msg.linear.x)}")
        self.get_logger().info(f"Yaw: {int(slave_msg.angular.z)}")
        self.get_logger().info(f"Pitch: {int(slave_msg.angular.y)}\n")

        
def main(args=None):
    rclpy.init(args=args)
    node = SnakeServerNode()
    rclpy.spin(node)
    rclpy.shutdown()