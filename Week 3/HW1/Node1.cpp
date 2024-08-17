#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sstream>

using namespace std;
using namespace ros;
using namespace std_msgs;

int received_data = 1;
Publisher talker;

void inputCallback(const Int32::ConstPtr& msg)
{
  received_data = msg->data;

  // 2 second delay
  Duration(2.0).sleep();

  // publish
  Int32 out_msg;
  out_msg.data = received_data + 1;
  ROS_INFO("%d + 1 = %d", received_data, out_msg.data);
  talker.publish(out_msg);
}

int main(int argc, char **argv)
{
  // initinalize ROS node
  init(argc, argv, "Node_1");

  // build node handle
  NodeHandle n;

  // set publisher and subscriber
  talker = n.advertise<Int32>("topic_12", 1000);
  Subscriber subscriber = n.subscribe("topic_41", 1000, inputCallback);

  // 5 second delay
  Duration(5.0).sleep();

  // first publish
  Int32 out_msg;
  out_msg.data = received_data;
  ROS_INFO("Start !");
  talker.publish(out_msg);

  while (ok())
  {
    spinOnce();
  }

  return 0;
}