cmake_minimum_required(VERSION 3.5)
project(sonar_control)


### Compile options
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
include_directories(
  include
)

# Target
## obstacle_collision_checker_node
ament_auto_add_library(sonar_control SHARED
  src/sonar_control_node.cpp
)

rclcpp_components_register_node(sonar_control
  PLUGIN "SonarControlNode"
  EXECUTABLE sonar_control_node
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package(INSTALL_TO_SHARE
  launch
)
