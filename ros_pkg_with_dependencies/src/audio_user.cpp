#include "ros/ros.h"
#include "audio_common_msgs/AudioData.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "audio_user");

  audio_common_msgs::AudioData data;

  ROS_INFO("Have audio data.");

  return 0;
}
