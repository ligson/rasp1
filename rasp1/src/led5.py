import RPi.GPIO as GPIO
import time

LED_0F = [
    # 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x8C, 0xBF, 0xC6, 0xA1, 0x86, 0xFF, 0xbf]
LED = []

DIO = 13
RCLK = 19
SCLK = 26

GPIO.setmode(GPIO.BCM)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)


def LED_OUT(ch):
    for i in range(8, 1, -1):
        if ch & 0x80:
            GPIO.output(DIO, True)
        else:
            GPIO.output(DIO, False)
        ch <<= 1
        GPIO.output(SCLK, False)
        GPIO.output(SCLK, True)


def LED8_Display():
    LED_OUT(1)
    GPIO.output(RCLK, False)
    GPIO.output(RCLK, True)


def loop():
    LED8_Display()


if __name__ == '__main__':
    LED[0] = 1
    LED[1] = 2
    LED[2] = 3
    LED[3] = 4
    LED[4] = 5
    LED[5] = 6
    LED[6] = 7
    LED[7] = 8
    n = True
    try:
        while True:
            time.sleep(0.5)
            loop()
            GPIO.output(21, n)
            if n:
                GPIO.output(21, n)
                n = False
            else:
                n = True

    except KeyboardInterrupt:
        pass
GPIO.cleanup()
