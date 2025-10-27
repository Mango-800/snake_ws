#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
import tkinter as tk
from geometry_msgs.msg import Twist

class SnakePublisherNode(Node):
    def __init__(self):
        super().__init__("snake_publisher_node")
        self.get_logger().info("snake publisher node has been started")

        self.speed = 0.0
        self.yaw = 0.0
        self.pitch = 0.0
        self.module = 1.0
        self.MAX_SPEED = 255.0
        self.speedList = [self.MAX_SPEED * 0.4, self.MAX_SPEED * 0.5, self.MAX_SPEED * 0.75, self.MAX_SPEED]
        self.speedCount = 0
        self.currentSpeed = self.speedList[self.speedCount]
        self.speedPressed = False
        self.yawPressed = False
        self.pitchPressed = False
        self.prevSpeed = self.speed
        self.prevYaw = self.yaw
        self.prevPitch = self.pitch
        self.prevModule = self.module

        self.module_publisher = self.create_publisher(Twist, "snake_module", 10)

        self.root = tk.Tk()
        self.root.title("Control Snake")
        self.label_speed = tk.Label(self.root, text=f"Speed: {self.currentSpeed}")
        self.label_speed.pack()
        self.label_module = tk.Label(self.root, text=f"Module: {self.module}")
        self.label_module.pack()
        self.root.geometry("400x300")

        self.root.bind("<KeyPress-w>", self.forward)
        self.root.bind("<KeyPress-s>", self.backward)
        self.root.bind("<KeyPress-d>", self.yawRight)
        self.root.bind("<KeyPress-a>", self.yawLeft)
        self.root.bind("<KeyPress-p>", self.pitchUp)
        self.root.bind("<KeyPress-l>", self.pitchDown)
        self.root.bind("<Up>", self.increaseSpeed)
        self.root.bind("<Down>", self.decreaseSpeed)
        self.root.bind("<KeyRelease-w>", self.speedReleased)
        self.root.bind("<KeyRelease-s>", self.speedReleased)
        self.root.bind("<KeyRelease-d>", self.yawReleased)
        self.root.bind("<KeyRelease-a>", self.yawReleased)
        self.root.bind("<KeyRelease-p>", self.pitchReleased)
        self.root.bind("<KeyRelease-l>", self.pitchReleased)
        self.root.bind("<KeyPress-0>", self.module0)
        self.root.bind("<KeyPress-1>", self.module1)
        self.root.bind("<KeyPress-2>", self.module2)
        self.root.bind("<KeyPress-3>", self.module3)
        self.root.mainloop()

    def forward(self, event):
        self.speed = self.currentSpeed
        self.speedPressed = True
        self.publishModule()

    def backward(self, event):
        self.speed = -self.currentSpeed
        self.speedPressed = True
        self.publishModule()
    
    def increaseSpeed(self, event):
        if self.speedCount < 3:
            self.speedCount += 1
        self.currentSpeed = self.speedList[self.speedCount]
        self.label_speed.config(text=f"Speed: {self.currentSpeed}")

    def decreaseSpeed(self, event):
        if self.speedCount > 0:
            self.speedCount -= 1
        self.currentSpeed = self.speedList[self.speedCount]
        self.label_speed.config(text=f"Speed: {self.currentSpeed}")
    
    def yawRight(self, event):
        self.yaw = 255.0
        self.yawPressed = True
        self.publishModule()

    def yawLeft(self, event):
        self.yaw = -255.0
        self.yawPressed = True
        self.publishModule()

    def pitchUp(self, event):
        self.pitch = 255.0
        self.pitchPressed = True
        self.publishModule()

    def pitchDown(self, event):
        self.pitch = -255.0
        self.pitchPressed = True
        self.publishModule()

    def speedReleased(self, event):
        self.speedPressed = False
        self.root.after(10, self.speed_key_released)

    def speed_key_released(self):  
        if not self.speedPressed: 
            self.speed = 0.0
            self.publishModule()

    def yawReleased(self, event):
        self.yawPressed = False
        self.root.after(10, self.yaw_key_released)

    def yaw_key_released(self):  
        if not self.yawPressed: 
            self.yaw = 0.0
            self.publishModule()

    def pitchReleased(self, event):
        self.pitchPressed = False
        self.root.after(10, self.pitch_key_released)

    def pitch_key_released(self):  
        if not self.pitchPressed: 
            self.pitch = 0.0
            self.publishModule()

    def module0(self, event):
        if self.module != 0.0:
            self.module = 0.0
            self.configModule()
            self.publishModule()

    def module1(self, event):
        if self.module != 1.0:
            self.module = 1.0
            self.configModule()
            self.publishModule()

    def module2(self, event):
        if self.module != 2.0:
            self.module = 2.0
            self.configModule()
            self.publishModule()

    def module3(self, event):
        if self.module != 3.0:
            self.module = 3.0
            self.configModule()
            self.publishModule()

    def configModule(self):
        self.label_speed.config(text=f"Speed: {self.currentSpeed}")
        self.label_module.config(text=f"Module: {int(self.module)}")
        self.speed = 0.0
        self.yaw = 0.0
        self.pitch = 0.0

    def publishModule(self):
        if (self.speed != self.prevSpeed) or (self.yaw != self.prevYaw) or (self.pitch != self.prevPitch) or (self.module != self.prevModule):
            self.prevModule = self.module
            self.prevSpeed = self.speed
            self.prevYaw = self.yaw
            self.prevPitch = self.pitch

            moduleMsg = Twist()
            moduleMsg.linear.y = self.module
            moduleMsg.linear.x = self.speed
            moduleMsg.angular.z = self.yaw
            moduleMsg.angular.y = self.pitch

            self.module_publisher.publish(moduleMsg)   
            self.get_logger().info(f"Module: {int(moduleMsg.linear.y)}")
            self.get_logger().info(f"Speed: {int(moduleMsg.linear.x)}")
            self.get_logger().info(f"Yaw: {int(moduleMsg.angular.z)}")
            self.get_logger().info(f"Pitch: {int(moduleMsg.angular.y)}\n")         

def main(args=None):
    rclpy.init(args=args)
    node = SnakePublisherNode()
    rclpy.spin(node)
    rclpy.shutdown()