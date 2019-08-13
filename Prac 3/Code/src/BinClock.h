#ifndef BINCLOCK_H
#define BINCLOCK_H

//Some reading (if you want)
//https://stackoverflow.com/questions/1674032/static-const-vs-define-vs-enum

// Function definitions
int hFormat(int hours);
void lightHours(int units);
void lightMins(int units);
int hexCompensation(int units);
int decCompensation(int units);
void initGPIO(void);
void secPWM(int units);
void hourInc(void);
void minInc(void);
void toggleTime(void);

// define constants
const char RTCAddr = 0x6f;
const char SEC = 0x00; // see register table in datasheet
const char MIN = 0x01;
const char HOUR = 0x02;
const char TIMEZONE = 2; // +02H00 (RSA)

// define pins
const int LEDS[] = {0,2,3,25,7,22,21,27,4,6}; //H0-H3, M0-M4
// using H0-H3 for hours
// BCM NUms : 17, 27, 22, 26, 4, 6, 5, 16, 23, 25 
//Are any of the LED pins here pwm pins? GPIO NUMS 12 18 13 19 BOARD NUMS 12 32 33 35

// YES. We are using GPIO_GEN1 or PWM0
const int SECS = 1;
const int BTNS[] = {5,30}; // B0, B1


#endif
