#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from jarvis_msgs.msg import Command
class PythonExample:
    def __init__(self):
        self.sub = rospy.Subscriber("/command", String, self.sub_callback)
        self.pub = rospy.Publisher("/jarvis/command", Command, queue_size = 10)
        self.timer = rospy.Timer(rospy.Duration(0.1),self.timer_callback)
        self.command = ""
        self.command_recived = False
        self.current_time = rospy.get_rostime()
        self.turn_recieved = False
        self.enable = False
    
    def sub_callback(self, data):
        self.command = data.data
        self.command_recived = True

    def timer_callback(self, data):
        if self.command == "jarvis":
            self.enable = True
            self.current_time = rospy.get_rostime()
        
        if (rospy.get_rostime() - self.current_time >= rospy.Duration(4.0)):
            self.enable = False
        if self.enable:
            if self.command_recived:
                # === simple === #
                simple_msg = Command()
                simple_msg.command_type.data = 2
                
                if not self.turn_recieved:
                    if self.command == "forward":
                        simple_msg.arguments = ["forward"]
                        self.enable = False
                    elif self.command == "back":
                        simple_msg.arguments = "back"
                        self.enable = False
                    elif self.command == "stop":
                        simple_msg.arguments = "stop"
                        self.enable = False
                    elif self.command == "left":
                        simple_msg.arguments = ["left"]
                        self.enable = False
                    elif self.command == "right":
                        simple_msg.arguments = "right"
                        self.enable = False
                    elif self.command == "turn":
                        self.turn_recieved = True
                        current_time = rospy.get_rostime()
                
                if self.turn_recieved:
                    if self.command == "left":
                        simple_msg.arguments = ["turn","left"]
                        self.enable = False
                        self.turn_recieved = False
                    elif self.command == "right":
                        simple_msg.arguments = ["turn","right"]
                        self.enable = False
                        self.turn_recieved = False
                    elif self.command == "stop":
                        simple_msg.arguments = ["turn","stop"]
                        self.enable = False
                        self.turn_recieved = False

                if not self.enable:
                    self.pub.publish(simple_msg)

    def run(self,rate):
        rate.sleep()

def main():
    rospy.init_node('Logic')
    
    t = PythonExample()
    
    rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        t.run(rate)

if __name__=="__main__":
    main()
