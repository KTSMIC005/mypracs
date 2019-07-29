import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

on_btn = 17
off_btn = 27
GPIO.setup(on_btn, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(off_btn, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)


led0 = 22
GPIO.setup(led0, GPIO.OUT, initial = GPIO.HIGH)


GPIO.add_event_detect(on_btn, GPIO.FALLING, bouncetime = 20) 
GPIO.add_event_detect(off_btn, GPIO.RISING, bouncetime = 20) 

    

# Logic that you write
def main():
    
    global led0
    global on_btn
    global off_btn 

    if GPIO.event_detected(on_btn):
        #pin 23 is up button. HIGH connected
        print('on button pressed')
        GPIO.output(led0, GPIO.HIGH)
    
    if GPIO.event_detected(off_btn):
        #pin 24 is down button. HIGH connected
        print('Off button pressed')
        GPIO.output(led0, GPIO.LOW)





# Only run the functions if 
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
            # print("off button is {}\n on button is {}".format(GPIO.input(on_btn), GPIO.input(off_btn)))
            time.sleep(.01)
            
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
        GPIO.cleanup()
    # except e:
    #     GPIO.cleanup()
    #     print("Some other error occurred")
    #     print(e.message)
