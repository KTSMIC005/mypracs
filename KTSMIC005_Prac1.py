#!/usr/bin/python3
"""
Python Practical Template
Keegan Crankshaw
Readjust this Docstring as follows:
Names: Michael Katsoulis 
Student Number: KTSMIC005
Prac: Prac 1
Date: 30 July 2019
"""

# import Relevant Librares
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)


count = 0
up_btn = 23
down_btn = 24
GPIO.setup(up_btn, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(down_btn, GPIO.IN, pull_up_down = GPIO.PUD_UP)


led0 = 17
led1 = 27
led2 = 22
GPIO.setup(led0, GPIO.OUT, initial = GPIO.HIGH)
GPIO.setup(led1, GPIO.OUT, initial = GPIO.HIGH)
GPIO.setup(led2, GPIO.OUT, initial = GPIO.HIGH)

GPIO.add_event_detect(up_btn, GPIO.FALLING, bouncetime = 300) 
GPIO.add_event_detect(down_btn, GPIO.FALLING, bouncetime = 300) 

def display(count):
 
    if (count // 4):
        #Turn on 2^2 led (led2)
        GPIO.output(led2, GPIO.HIGH)
        count = count % 4
    else:
        GPIO.output(led2, GPIO.LOW)
    
    if count //2:
        GPIO.output(led1, GPIO.HIGH)
        count = count % 2
    else:
        GPIO.output(led1, GPIO.LOW)
    
    if count:
        GPIO.output(led0, GPIO.HIGH)
    else:
        GPIO.output(led0, GPIO.LOW)

    

# Logic that you write
def main():
    
    global count
    if GPIO.event_detected(up_btn):
        #pin 23 is up button. HIGH connected
        print('Up button pressed')
        count +=1
        print ("Count is {}".format(count))
    
    if GPIO.event_detected(down_btn):
        #pin 24 is down button. HIGH connected
        print('Down button pressed')
        count -=1
        print ("Count is {}".format(count))

    if count ==8:
        count = 0
    if count == -1:
        count = 7
    
    display(count)




# Only run the functions if 
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
            time.sleep(.02)
            
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
        GPIO.cleanup()
    # except e:
    #     GPIO.cleanup()
    #     print("Some other error occurred")
    #     print(e.message)
