#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Joy.h>
#include <sstream>

using namespace std;

/*
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
*/

void Callback(const sensor_msgs::Joy::ConstPtr& joy)
{
  int b = joy->buttons[1];
  float f = joy->axes[1];
  stringstream ssb;
  stringstream ssf;
  ssb << b;
  ssf << f;
  string strb = ssb.str();
  string strf = ssf.str();
  ROS_INFO("buttons[B]:[%s]", strb.c_str());
  ROS_INFO("axes[f]:[%s]", strf.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joy", 1000, Callback);

  ros::spin();

  return 0;
}
