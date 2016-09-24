import RPi.GPIO as GPIO
import time
import random

GPIO.setmode(GPIO.BCM)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)

pwm1 = GPIO.PWM(13, 1)
pwm2 = GPIO.PWM(19, 1)
pwm3 = GPIO.PWM(26, 1)

pwm1.start(0)
pwm2.start(0)
pwm3.start(0)

def changeColor(r, g, b):
    pwm1.ChangeDutyCycle(r)
    pwm2.ChangeDutyCycle(g)
    pwm3.ChangeDutyCycle(b)
    
if __name__ == '__main__':
    try:
        while True:
            n1 = int(random.random()*100)
            n2 = int(random.random()*100)
            n3 = int(random.random()*100)
            changeColor(n1,n2,n3)
            time.sleep(0.5)
    except KeyboardInterrupt:
        pass
GPIO.cleanup()

pwm1.stop()
pwm2.stop();
pwm3.stop();

