cmake_minimum_required(VERSION 2.8.3)
project(ros_pkg_with_dependencies)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  audio_common_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_pkg_with_dependencies
CATKIN_DEPENDS audio_common_msgs
DEPENDS system_lib
)

###########
## Build ##
###########

add_executable(audio_user src/audio_user.cpp)
target_link_libraries(audio_user ${catkin_LIBRARIES})
add_dependencies(audio_user ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
