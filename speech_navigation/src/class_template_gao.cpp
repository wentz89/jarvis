//#include "ros/ros.h"
#include "class_template_gao.h"
#include <ros/ros.h>
#include<std_msgs/String.h>
#include<jarvis_msgs/Command.h>

ClassTemplate::~ClassTemplate()
{
}

ClassTemplate::ClassTemplate(ros::NodeHandle &nh):n_(&nh)
{
   time_point=false;

    ROS_INFO("ClassTemplate loading Publisher");

    //Publisher

   pub_ = n_->advertise<jarvis_msgs::Command>("/jarvis/command", 10);

    //Subscriber
    ROS_INFO("ClassTemplate loading Subscriber");
    sub_ = n_->subscribe<std_msgs::String>("/command",10, &ClassTemplate::SubCallback, this);

    //ServiceServer
   // ROS_INFO("ClassTemplate loading service");
  //  service_ = n_->advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response>("/template/Service", boost::bind(&ClassTemplate::ServiceCallback, this,_1,_2));//_1,_2 bedeutet zwei Argumente an ServiceCallback (wird von boost::bind benötigt)
    //std_srvs/Empty.h in header included

    //Timer
    ROS_INFO("ClassTemplate loading timer");

    timer_ = n_->createTimer(ros::Duration(1), &ClassTemplate::timerCallback, this);
    // triggert je 2 sekunden/ROS_INFO("Current Info Number: %f",info_num_);
    //enabled_ = false;

    // service client
    //client_ = n->serviceClient<std_srvs::Empty>("/any_service");

    // other Stuff
    info_num_ = 0.0;
    enabled_ = false;

    // ...
    ROS_INFO("ClassTemplate loaded");
}

void ClassTemplate::timerCallback(const ros::TimerEvent& e)
{
    //enabled_ = false;
    jarvis_msgs::Command msg;
    std::vector<std::string> args;
    ros::Duration  four_sec(4.0);
    if(time_point==false){
    current_time=ros::Time::now();
    }
     if(ros::Time::now()-current_time>four_sec){
       args.push_back("you " "are " "too " "slow");
       msg.arguments = args;
       enabled_=false;
       msg_recived=false;
       turn=false;
       current_time=ros::Time::now();
       time_point=false;
    }
    if(enabled_==true){
        if(command_=="stop"){
            ROS_INFO("stop");
        args.push_back("stop");
        msg.arguments = args;
        enabled_=false;
        turn=false;
        msg_recived=false;
        current_time=ros::Time::now();
        time_point=false;
        }
       if(command_=="jarvis"){
        ROS_INFO("jarivs");
        msg_recived=true;
        enabled_=false;
        time_point=true;
       }

    if(msg_recived){
//========================simple message=======================//
         if(turn==false){          
            if(command_ =="forward"){
            args.push_back("forward");
            msg.arguments=args;
            msg.command_type=2;
            enabled_ =false;
            msg_recived=false;
            current_time=ros::Time::now();
                 }
                 if(command_ =="left"){
                    args.push_back("left");
                    msg.arguments = args;
                    msg.command_type=2;
                    enabled_ =false;
                    msg_recived=false;
                    current_time=ros::Time::now();
                    time_point=false;

                 }

                 if(command_ =="right"){
                     args.push_back("right");
                     msg.arguments = args;
                     msg.command_type=2;
                     enabled_ =false;
                     msg_recived=false;
                     current_time=ros::Time::now();
                     time_point=false;
                 }
         }
                 if(command_ =="turn"){
                     turn=true;
                      ROS_INFO("turn");
                 }
                    if(turn==true){
                    if(command_ =="left"){
                        turn=false;
                        ROS_INFO("left");
                        args.push_back("turn""left");
                        msg.arguments = args;
                        msg.command_type=2;
                        enabled_ =false;
                        msg_recived=false;
                        current_time=ros::Time::now();
                        time_point=false;
                        }
                    if(command_ =="right"){
                        turn=false;
                        ROS_INFO("right");
                        args.push_back("turn""right");
                        msg.arguments = args;
                        msg.command_type=2;
                        enabled_ =false;                      
                        msg_recived=false;
                        current_time=ros::Time::now();
                        time_point=false;

                       }
                    }

    }

    }

pub_.publish(msg);

}


    /*bool ClassTemplate::ServiceCallback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
    {
        this->enabled_ = true;
        std_msgs::Float32 data;
        data.data = info_num_ + 1.0;
        ROS_INFO("Publish Info Number: %f",data.data);
        this->pub_.publish(data);
        return true;
    }*/

    void ClassTemplate::SubCallback(std_msgs::String datas)
    {
        command_ = datas.data;
        enabled_ = true;
        time_point=true;

        //addOne(datas.data);
        ROS_INFO("got data");
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
