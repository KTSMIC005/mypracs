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
GPIO.setup([up_btn, down_btn], GPIO.IN, pull_up_down = GPIO.PUD_UP)


led0 = 17
led1 = 27
led2 = 22
GPIO.setup([led0, led1, led2], GPIO.OUT, initial = GPIO.LOW)

def display(count):
    count 
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

    return count


    

    

# Logic that you write
def main():
    GPIO.add_event_detect([up_btn,down_btn], GPIO.RISING) 
    global count
    if GPIO.event_detected(up_btn):
        #pin 23 is up button. HIGH connected
        print('Button pressed')
        count +=1
    
    if GPIO.event_detected(down_btn):
        #pin 23 is up button. HIGH connected
        print('Button pressed')
        count -=1
    #pin 24 is  button 2 hi/low

    
    #DoSomething if button is pressed
    



    if count >8:
        count = count%8
    
    display(count)




# Only run the functions if 
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
            time.sleep(20)
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
        GPIO.cleanup()
    except e:
        GPIO.cleanup()
        print("Some other error occurred")
        print(e.message)
