import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    example_dir = get_package_share_directory('castle_maker')


    plansys2_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(
            get_package_share_directory('plansys2_bringup'),
            'launch',
            'plansys2_bringup_launch_monolithic.py')),
        launch_arguments={
          'model_file': example_dir + '/pddl/castle-maker-durative-domain.pddl'}.items())
    pickup_cmd = Node(
        package='castle_maker',
        executable='pickup_action_node',
        name='pickup_action_node',
        output='screen',
        parameters=[])

    putdown_cmd = Node(
        package='castle_maker',
        executable='putdown_action_node',
        name='putdown_action_node',
        output='screen',
        parameters=[]) 
        
    stack_cmd = Node(
        package='castle_maker',
        executable='stack_action_node',
        name='stack_action_node',
        output='screen',
        parameters=[])
    ld = LaunchDescription()
    ld.add_action(plansys2_cmd)
    ld.add_action(pickup_cmd)
    ld.add_action(putdown_cmd)
    ld.add_action(stack_cmd)

    return ld
