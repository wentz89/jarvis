#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"



std::string com;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ros::NodeHandle n;
  ros::Publisher direction_pub =n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  com=msg->data.c_str();
  if (com=="forward") {
      ROS_INFO("In forward mode");
      geometry_msgs::Twist geom;
      geom.linear.x=0.5;
      geom.linear.y=0.0;
      geom.linear.z=0.0;
      geom.angular.x=0.0;
      geom.angular.y=0.0;
      geom.angular.z=0.0;
      direction_pub.publish(geom);
  }
  else if (com=="back"){
      geometry_msgs::Twist geom;
      geom.linear.x=-5.0;
      direction_pub.publish(geom);
  }
  else if (com=="left"){
      geometry_msgs::Twist geom;
      geom.linear.y=-5.0;
      direction_pub.publish(geom);
  }
  else if (com=="right"){
      geometry_msgs::Twist geom;
      geom.linear.y=5.0;
      direction_pub.publish(geom);
  }
  else if (com=="turn"){
      geometry_msgs::Twist geom;
      geom.angular.z=5.0;
      direction_pub.publish(geom);
  }

  else if (com=="hold"){
  }
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */


  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub = n.subscribe("command", 1000, chatterCallback);

  /**
   * commands: start, back, hold, left, right, turn
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}

