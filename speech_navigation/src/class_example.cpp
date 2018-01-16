//#include "ros/ros.h"
#include "class_template.h"
#include <ros/ros.h>

//Deconstructor
ClassTemplate::~ClassTemplate()
{
}

ClassTemplate::ClassTemplate(ros::NodeHandle &nh):n_(&nh)
{
    ROS_INFO("ClassTemplate loading Publisher");

    //Publisher
    pub_ = n_->advertise<std_msgs::Float32>("/info_topic", 1);//std_msgs/Float32.h in header included

    //Subscriber
    ROS_INFO("ClassTemplate loading Subscriber");
    sub_ = n_->subscribe<std_msgs::Float32>("/info_topic",10, &ClassTemplate::SubCallback, this);

    //ServiceServer
    ROS_INFO("ClassTemplate loading service");
    service_ = n_->advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response>("/template/Service", boost::bind(&ClassTemplate::ServiceCallback, this,_1,_2));//_1,_2 bedeutet zwei Argumente an ServiceCallback (wird von boost::bind benötigt)
    //std_srvs/Empty.h in header included

    //Timer
    ROS_INFO("ClassTemplate loading timer");
    timer_ = n_->createTimer(ros::Duration(2.0), &ClassTemplate::timerCallback, this);
    // triggert je 2 sekunden
    
    // service client
    //client_ = n->serviceClient<std_srvs::Empty>("/any_service");
    
    // other Stuff
    info_num_ = 0.0;
    // ...
    ROS_INFO("ClassTemplate loaded");
}

void ClassTemplate::timerCallback(const ros::TimerEvent& e)
{
    ROS_INFO("Current Info Number: %f",info_num_);
    enabled_ = false;
}

bool ClassTemplate::ServiceCallback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
    this->enabled_ = true;
    std_msgs::Float32 data;
    data.data = info_num_ + 1.0;
    ROS_INFO("Publish Info Number: %f",data.data);
    this->pub_.publish(data);
    return true;
}

void ClassTemplate::SubCallback(std_msgs::Float32 datas)
{
    addOne(datas.data);
    ROS_INFO("Got Info Number: %f",datas.data);
}

void ClassTemplate::addOne(float num)
{
    info_num_ = info_num_ + num;
}

/****************(Alternative)
ClassTemplate::run()
{
    ros::spinOnce();
    loop_rate.sleep();
    // do other stuff
}
****************/

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
    // Alternative zu spinOnce und loop_rate.sleep
    // definiere eine "run()"-Funktion
    // m.run()
  }


  return 0;
}
