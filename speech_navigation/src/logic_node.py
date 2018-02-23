#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from jarvis_msgs.msg import Command
class PythonExample:
    def __init__(self):
        self.sub = rospy.Subscriber("/command", String, self.sub_callback)
        self.pub = rospy.Publisher("/jarvis/command", Twist, queue_size = 10)
        self.timer = rospy.Timer(rospy.Duration(0.1),self.timer_callback)
        self.command = ""
        self.command_recived = False
    
    def sub_callback(self, data):
        self.command = data.data
        self.command_recived = True

    def timer_callback(self, data):
        turn_recieved = False
        if self.command == "jarvis":
            enable = True
            current_time = rospy.get_rostime()
        if (rospy.get_rostime() - current_time >= 4.0):
            enable = False
        if enable:
            if self.command_recived:
                # === simple === #
                simple_msg = Command()
                simple_msg.command_type = 2
                
                if not turn_recieved:
                    if self.command == "forward":
                        simple_msg.arguments = "forward"
                        enable = False
                    elif self.command == "back":
                        simple_msg.arguments = "back"
                        enable = False
                    elif self.command == "stop":
                        simple_msg.arguments = "stop"
                        enable = False
                    elif self.command == "left":
                        simple_msg.arguments = "left"
                        enable = False
                    elif self.command == "right":
                        simple_msg.arguments = "right"
                        enable = False
                    elif self.command == "turn":
                        turn_recieved = True
                        current_time = rospy.get_rostime()
                
                if turn_recieved:
                    if self.command == "left":
                        simple_msg.arguments = ["turn","left"]
                        enable = False
                    elif self.command == "right":
                        simple_msg.arguments = ["turn","right"]
                        enable = False
                    elif self.command == "stop":
                        simple_msg.arguments = ["turn","stop"]
                        enable = False

                self.pub.publish(simple_msg)

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
