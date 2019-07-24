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
import time.sleep as sleep
GPIO.setmode(GPIO.BCM)


count = 0
up_button = 23
GPIO.setup(up_button, GPIO.IN, pull_up_down = GPIO.PUD_UP)
down_button = 24
GPIO.setup(down_button, GPIO.IN, pull_up_down = GPIO.PUD_UP)


led0 = 17
GPIO.setup(led0, GPIO.OUT, initial = GPIO.LOW)
led1 = 27
GPIO.setup(led1, GPIO.OUT, initial = GPIO.LOW)
led2 = 22
GPIO.setup(led2, GPIO.OUT, initial = GPIO.LOW)

def display():
    tmp_count = count
    if (tmp_count // 4):
        #Turn on 2^2 led (led2)
        GPIO.output(led2, GPIO.HIGH)
        tmp_count = tmp_count % 4
    else:
        GPIO.output(led2, GPIO.LOW)
    
    if tmp_count //2:
        GPIO.output(led1, GPIO.HIGH)
        tmp_count = tmp_count % 2
    else:
        GPIO.output(led1, GPIO.LOW)
    
    if tmp_count:
        GPIO.output(led0, GPIO.HIGH)
    else:
        GPIO.output(led0, GPIO.LOW)


    

    

# Logic that you write
def main():
    #pin 23 is button 1 hi/low
    #pin 24 is  button 2 hi/low

    
    #DoSomething if button is pressed
    



    if count >8:
        count = count%8
    
    display()


# Only run the functions if 
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
            sleep(20)
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
        GPIO.cleanup()
    except e:
        GPIO.cleanup()
        print("Some other error occurred")
        print(e.message)
