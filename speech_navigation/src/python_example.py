#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist
class PythonExample:
    def __init__(self):
        self.sub = rospy.Subscriber("/command", String, self.sub_callback)
        self.pub = rospy.Publisher("/cmd_vel", Twist, queue_size = 10)
        self.timer = rospy.Timer(rospy.Duration(0.1),self.timer_callback)
        self.command = ""
        self.command_recived = False
    
    def sub_callback(self, data):
        self.command = data.data
        self.command_recived = True

    def timer_callback(self, data):
        geom = Twist()
        geom.linear.x = 0.0
        geom.linear.y = 0.0
        geom.linear.z = 0.0
        geom.angular.x = 0.0
        geom.angular.y = 0.0
        geom.angular.z = 0.0
        if self.command_recived:
            if self.command == "forward":
                geom.linear.x = 0.5
            elif self.command == "back":
                geom.linear.x = -0.5

    def run(self,rate):
        rate.sleep()

def main():
    rospy.init_node('Test')
    
    t = PythonExample()
    
    rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        t.run(rate)

if __name__=="__main__":
    main()
