import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)

pwm1 = RPi.GPIO.PWM(13, 0)
pwm2 = RPi.GPIO.PWM(19, 0)
pwm3 = RPi.GPIO.PWM(26, 0)

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
            changeColor(255, 0, 0)
            time.sleep(0.5)
    except KeyboardInterrupt:
        pass
GPIO.cleanup()

pwm1.stop()
pwm2.stop();
pwm3.stop();

