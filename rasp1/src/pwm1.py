# coding=UTF-8
'''
Created on 2016年9月24日

@author: ligso
'''
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.OUT)

pwm = RPi.GPIO.PWM(21, 50)
pwm.start(0)

if __name__ == '__main__':
    try:
        while True:
            for i in xrange(0, 100, 2):
                pwm.ChangeDutyCycle(i)
                time.sleep(0.01)
            for i in xrange(100, 0, 2):
                pwm.ChangeDutyCycle(i)
                time.sleep(0.01)
    except KeyboardInterrupt:
        pass
pwm.stop()
GPIO.cleanup()