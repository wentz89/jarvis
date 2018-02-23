#ifndef CLASS_TEMPLATE_HH
#define CLASS_TEMPLATE_HH

// ros stuff
#include <ros/ros.h>
// ros messages stuff
#include <std_msgs/Float32.h>
#include <std_srvs/Empty.h>
#include "geometry_msgs/Twist.h"

// dynamic reconfigure stuff
//#include <dynamic_reconfigure/server.h>
// boost stuff
#include <boost/shared_ptr.hpp>

//other Stuff
#include "math.h"


  class ClassTemplate 
  {
    
    public:
      ClassTemplate(ros::NodeHandle &nh);
      ~ClassTemplate();

      // public Functions for callbacks
      bool ServiceCallback(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
      void SubCallback(std_msgs::Float32 datas);
      void timerCallback(const ros::TimerEvent& e);

    private:
      //private Functions
      void addOne(float num);
      String com;
      
      
      //Class Variables
      float                                 info_num_;
      bool                                  enabled_;

      //ROS Stuff
      ros::NodeHandle                       *n_;
      ros::Publisher                        pub_;
      ros::ServiceServer                    service_;
      ros::Subscriber                       sub_;
      ros::Timer                            timer_;
      
  };// Class End
#endif

