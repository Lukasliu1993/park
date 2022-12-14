cmake_minimum_required(VERSION 3.5)
project(osqp_interface)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Ofast)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3 REQUIRED)

find_package(osqp_vendor REQUIRED)

find_package(osqp REQUIRED)
get_target_property(OSQP_INCLUDE_SUB_DIR osqp::osqp INTERFACE_INCLUDE_DIRECTORIES)
get_filename_component(OSQP_INCLUDE_DIR ${OSQP_INCLUDE_SUB_DIR} PATH)

ament_auto_add_library(osqp_interface SHARED
  src/osqp_interface.cpp
  src/csc_matrix_conv.cpp
  include/osqp_interface/osqp_interface.hpp
  include/osqp_interface/csc_matrix_conv.hpp
)

target_include_directories(osqp_interface PUBLIC "${OSQP_INCLUDE_DIR}")
ament_target_dependencies(osqp_interface Eigen3)
ament_target_dependencies(osqp_interface osqp_vendor)

# crucial so downstream package builds because osqp_interface exposes osqp.hpp
ament_export_include_directories("${OSQP_INCLUDE_DIR}")
# crucial so the linking order is correct in a downstream package: libosqp_interface.a should come before libosqp.a
ament_export_libraries(osqp::osqp)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(osqp_interface_test test/osqp_interface_test.cpp)
  target_link_libraries(osqp_interface_test osqp_interface ${EIGEN3_LIBRARIES})
endif()

ament_auto_package()
