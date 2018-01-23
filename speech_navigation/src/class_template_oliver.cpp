//#include "ros/ros.h"
#include "class_template_oliver.h"
#include <geometry_msgs/Twist.h>
//#include "std_msgs/String.h"

//Deconstructor
ClassTemplate::~ClassTemplate()
{
}

ClassTemplate::ClassTemplate(ros::NodeHandle &nh):n_(&nh)
{
    ROS_INFO("ClassTemplate loading Publisher");

    //Publisher
    pub_ = n_->advertise<geometry_msgs::Twist>("gazebo/cmd_vel", 1);

    //Subscriber
    ROS_INFO("ClassTemplate loading Subscriber");
    sub_ = n_->subscribe<std_msgs::String>("/command",10, &ClassTemplate::SubCallback, this);

    //ServiceServer
    ROS_INFO("ClassTemplate loading service");
    service_ = n_->advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response>("/template/Service", boost::bind(&ClassTemplate::ServiceCallback, this,_1,_2));//_1,_2 bedeutet zwei Argumente an ServiceCallback (wird von boost::bind benötigt)
    //std_srvs/Empty.h in header included

    //Timer
    ROS_INFO("ClassTemplate loading timer");
    timer_ = n_->createTimer(ros::Duration(2.0), &ClassTemplate::timerCallback, this);
    // triggert je 2 sekunden

    // ...
    ROS_INFO("ClassTemplate loaded");
}

void ClassTemplate::timerCallback(const ros::TimerEvent& e)
{
    enabled_ = false;
}

bool ClassTemplate::ServiceCallback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
    //this->enabled_ = true;
    //ROS_INFO("Publish Info: %s",data.data);
    //this->pub_.publish(data);
    //return true;
}

void ClassTemplate::SubCallback(std_msgs::String datas)
{
    geometry_msgs::Twist new_msg;
    if (level==0)
    {
        if (datas.data=="right")
        {
           new_msg.linear.y=0.2;
        }
        if (datas.data=="left")
        {
           new_msg.linear.y=-0.2;
        }
        if (datas.data=="forward")
        {
           new_msg.linear.x=0.2;
        }
        if (datas.data=="back")
        {
           new_msg.linear.x=-0.2;
        }
        if (datas.data=="turn")
        {
            new_msg.linear.x=0;
            new_msg.linear.y=0;
            new_msg.linear.z=0;
            level=1;
        }
        if (datas.data=="stop")
        {
            new_msg.linear.x=0;
            new_msg.linear.y=0;
            new_msg.linear.z=0;
            new_msg.angular.x=0;
            new_msg.angular.y=0;
            new_msg.angular.z=0;
        }
    }
    if (level==1)
    {
        if (datas.data=="left")
        {
            new_msg.angular.z=1;
            level=0;
        }
        if (datas.data=="right")
        {
            new_msg.angular.z=-1;
            level=0;
        }
        if (datas.data=="stop")
        {
            new_msg.linear.x=0;
            new_msg.linear.y=0;
            new_msg.linear.z=0;
            new_msg.angular.x=0;
            new_msg.angular.y=0;
            new_msg.angular.z=0;
            level=0;
        }
    }
    pub_.publish(new_msg);
    ROS_INFO("Got Info: %s",datas.data.c_str());
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "ClassTemplate");
  ros::NodeHandle nh;
  ros::Rate loop_rate(10); // 10hz
  
  while(ros::Time::isValid()==0)
  {
    ros::Duration(0.5).sleep();
    ROS_WARN("WAITING FOR TIME TO BECOME VALID");
  }
  
  ClassTemplate m(nh);
//  ClassTemplate m2(nh);
  
  while(ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
