cmake_minimum_required(VERSION 2.8.3)
project(ros_pkg_with_tests)

## Find catkin macros and libraries
find_package(catkin REQUIRED
  roscpp
  rospy)

###################################
## catkin specific configuration ##
###################################
catkin_package(
)

###########
## Build ##
###########

include_directories(src)

## Declare a C++ library
add_library(square
  src/square.cpp
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
catkin_add_gtest(${PROJECT_NAME}-test src/test/test_square.cpp)
if(TARGET ${PROJECT_NAME}-test)
  target_link_libraries(${PROJECT_NAME}-test square)
endif()

## Add folders to be run by python nosetests
catkin_add_nosetests(scripts/test)
