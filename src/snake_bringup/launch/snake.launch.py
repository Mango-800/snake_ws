import launch
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

#La función debe tener este nombre
def generate_launch_description():
    #Se crea el objeto del launcher
    ld = LaunchDescription()
    #Se instancian objetos d enodos
    motors_node = Node(package = "snake_motors", executable = "motors")
    server_node = Node(package = "snake_server", executable = "server")
    # Se agrega el comando para ejecutar el agente Micro-ROS
    #Para comunicaciòn Wifi
    #micro_ros_agent = ExecuteProcess(
    #    cmd=["ros2", "run", "micro_ros_agent", "micro_ros_agent", "udp6", "--port", "8001"],
    #    output="screen",
    #)
    #Para comunicaciòn serial
    micro_ros_agent = ExecuteProcess(
        cmd=["ros2", "run", "micro_ros_agent", "micro_ros_agent", "serial", "--dev", "/dev/ttyUSB0"],
        output="screen",
    )
    #Los nodos se agregan al launcher
    ld.add_action(motors_node)
    ld.add_action(server_node)
    ld.add_action(micro_ros_agent)
    #Se regresa el launcher con las configuraciones hechas
    return ld