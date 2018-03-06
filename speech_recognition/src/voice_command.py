#!/usr/bin/env python
from os import environ, path

from pocketsphinx.pocketsphinx import *
from sphinxbase.sphinxbase import *
import pyaudio

import roslib
import rospy

from geometry_msgs.msg import Twist
from std_msgs.msg import String

class Voice_Controller_EDS:

    def __init__(self):


        rospy.init_node('voice_controller_eds')
        rospy.on_shutdown(self.shutdown)

        event_topic = '/command'

        self.pub_ = rospy.Publisher(event_topic, String, queue_size=10)

        # Create a decoder with certain model
        config = Decoder.default_config()
        #config.set_string('-hmm', path.join(MODELDIR, 'en-us/en-us'))
        config.set_string('-hmm', '/usr/local/share/pocketsphinx/model/en-us/en-us')
        #config.set_string('-lm', path.join(MODELDIR, 'en-us/en-us.lm.bin'))
        config.set_string('-lm', '/usr/local/share/pocketsphinx/model/en-us/en-us.lm.bin')
        #config.set_string('-dict', path.join(MODELDIR, 'en-us/cmudict-en-us.dict'))
        #config.set_string('-dict', '/usr/local/share/pocketsphinx/model/en-us/cmudict-en-us.dict')
        config.set_string('-dict', '/home/alex/wentz_catkin_ws/src/jarvis/speech_recognition/model/model2.dict')

        config.set_string('-logfn', '/dev/null')
        # Decode streaming data.
        self.decoder = Decoder(config)

        self.run()

    def run(self):
        self.decoder.start_utt()

        bUseMic = True
        fpb = 4096*2

        self.bPrintAll = True

        if(bUseMic):

            p = pyaudio.PyAudio()
            self.stream = p.open(format=pyaudio.paInt16, channels=1, rate=8000, input_device_index=7, input=True, frames_per_buffer=fpb)

        #load recorded file
        else:
            pass
            #self.stream = open('/home/rauschenberger/Programs/Sphinx/pocketsphinx_test/data/jantest.raw', 'rb')


        while not rospy.is_shutdown():

            buf = self.stream.read(fpb)
            if buf:
                 self.decoder.process_raw(buf, False, False)
            else:
                break

            self.process_asr()


    def process_asr(self):

        if self.decoder.hyp() != None:

            words = [(seg.word) for seg in self.decoder.seg()]

            if self.bPrintAll:
                print ('Best hypothesis segments: ', words)
# words = "<s>word1, word2,speech, </s>"
            word = words[-1]

            if len(words) >2:
                if word =='</s>':
                    word = words[-2]

            if word !='</s>':
                print (word)

            self.pub_.publish(word)
#                if word =="back":
#                   self.pub_.publish("back")

#                elif word =="forward":
#                    self.pub_.publish("forward")

#                elif word =="left":
#                    self.pub_.publish("left")

#                elif word =="right":
#                    self.pub_.publish("right")

#                elif word =="stop":
#                    self.pub_.publish("stop")

#                elif word =="turn":
#                    self.pub_.publish("turn")

#                elif word =="lock":
#                    self.pub_.publish("lock")

#                elif word =="unlock":
#                    self.pub_.publish("unlock")

#                elif word =="jarvis":
#                    self.pub_.publish("jarvis")

            self.decoder.end_utt()
            self.decoder.start_utt()

    def shutdown(self):
        """
        command executed after Ctrl+C is pressed
        """
        rospy.loginfo("Stop voice command")
        ##self.pub_.publish(Twist())
        rospy.sleep(1)

if __name__ == '__main__':

    r = Voice_Controller_EDS()
