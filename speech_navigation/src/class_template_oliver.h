#ifndef CLASS_TEMPLATE_HH
#define CLASS_TEMPLATE_HH

// ros stuff
#include <ros/ros.h>
// ros messages stuff
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>

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
      void SubCallback(std_msgs::String datas);
      void timerCallback(const ros::TimerEvent& e);

    private:
      //private Functions

      
      
      //Class Variables
      bool                                  enabled_;
      int				    level;

      //ROS Stuff
      ros::NodeHandle                       *n_;
      ros::Publisher                        pub_;
      ros::ServiceServer                    service_;
      ros::Subscriber                       sub_;
      ros::Timer                            timer_;
      
  };// Class End
#endif

