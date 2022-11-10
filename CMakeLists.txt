cmake_minimum_required(VERSION 3.5)
project(castle_maker)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(plansys2_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
#find_package(darknet_ros_msgs REQUIRED)
find_package(plansys2_domain_expert REQUIRED)
find_package(plansys2_executor REQUIRED)
find_package(plansys2_planner REQUIRED)
find_package(plansys2_problem_expert REQUIRED)
find_package(plansys2_pddl_parser REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(dependencies
    rclcpp
    rclcpp_action
    plansys2_msgs
    plansys2_domain_expert
    plansys2_executor
    plansys2_planner
    plansys2_problem_expert
    plansys2_pddl_parser
    geometry_msgs   
    std_msgs 
    #darknet_ros_msgs
    )


add_executable(pickup_action_node src/pickup_action_node.cpp)
ament_target_dependencies(pickup_action_node ${dependencies})

add_executable(putdown_action_node src/putdown_action_node.cpp)
ament_target_dependencies(putdown_action_node ${dependencies})

add_executable(stack_action_node src/stack_action_node.cpp)
ament_target_dependencies(stack_action_node ${dependencies})

add_executable(action_controller_node src/action_controller_node.cpp)
ament_target_dependencies(action_controller_node ${dependencies})



install(DIRECTORY launch pddl DESTINATION share/${PROJECT_NAME})

install(TARGETS
  pickup_action_node
  putdown_action_node
  stack_action_node
  action_controller_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
endif()

ament_export_dependencies(${dependencies})

ament_package()
