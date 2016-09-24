# coding=UTF-8
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.OUT)

if __name__ == '__main__':
    print("xxxxx")
    try:
        while True:
            print("---")
            GPIO.output(21, GPIO.HIGH)
            time.sleep(1)
            GPIO.output(21, GPIO.LOW)
            time.sleep(1)
    except KeyboardInterrupt:
        print("正常退出")
        pass
GPIO.cleanup()
