import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)

if __name__ == '__main__':
    n = True
    try:
        while True:
            time.sleep(0.5)
            GPIO.output(21, n)
            if n:
                GPIO.output(21, n)
                n = False
            else:
                n = True
    except KeyboardInterrupt:
        pass
GPIO.cleanup()
