//#include "ros/ros.h"
#include "class_template_gao.h"
#include <ros/ros.h>
#include<std_msgs/String.h>
#include<jarvis_msgs/Command.msg>

//Deconstructor
ClassTemplate::~ClassTemplate()
{
}

ClassTemplate::ClassTemplate(ros::NodeHandle &nh):n_(&nh)
{
    ROS_INFO("ClassTemplate loading Publisher");

    //Publisher
    pub_ = n_->advertise<std_msgs::String>("/jarvis/command", 1);//std_msgs/Float32.h in header included

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
    
    // other tStuff
    info_num_ = 0.0;
    // ...
    ROS_INFO("ClassTemplate loaded");
}

void ClassTemplate::timerCallback(const ros::TimerEvent& e)
{
    ROS_INFO("you are to slow");
    flag= false;
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

void ClassTemplate::SubCallback(std_msgs::String datas)
{
      std_msgs::String argument;
      argument=datas;
      jarvis_msgs::comannd msg;
      flag=false;
      ClassTemplate.timer_=n_->createTimer(ros::Duration(4), timerCallback);
     if(argument.data="jarvis"&flag=true){
        

         if(argument.data=="forward"&flag=true){
            msg.arguments="jarvis_forward";
            msg.command_type=2;
         }
         if(argument.data=="left"&flag=true){
            msg.arguments="jarvis_left";
            msg.command_type=2;
         }
         if(argument.data=="right"&flag=true){
            msg.arguments="jarvis_left";
            msg.command_type=2;
         }
         if(argument.data=="turn"&flag=true){
             flag=false;
            if(argument.data="left"){
                msg.arguments="jarvis_turn_left";
                msg.command_type=2;
                }
            if(argument.data=="right"){
                msg.arguments="jarvis_turn_right";
                msg.command_type=2;
               }
         }
     }
   pub_1.publish(msg);
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
//  ClssTemplate m2(nh);
  
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
