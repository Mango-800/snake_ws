from setuptools import find_packages, setup

package_name = 'snake_server'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='tatsuki',
    maintainer_email='tatsuki@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "server = snake_server.snakeServer:main",
            "slave_1 = snake_server.slaveModule2:main",
            "slave_2 = snake_server.slaveMOdule3:main"
        ],
    },
)
