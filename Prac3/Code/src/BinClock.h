#ifndef BINCLOCK_H
#define BINCLOCK_H
#endif

// Function definitions
int hFormat(int hours);

void lightHours(int units);
void lightMins(int units);

int hexCompensation(int units);
int decCompensation(int units);

void initGPIO(void);
void cleanup(int);

void secPWM(int units);

void hourIncrement(void);
void minuteIncrement(void);

void toggleTime(void);
void setCurrentTime(void);

// define constants
const char RTCAddr  = 0x6f;     // Unique I2C Address for RTC
const char SEC      = 0x00;     // 0x00 is the Seconds Register Address (with bit 0 the RTC enabler)
const char MIN      = 0x01;     // 0x01 is the Minutes Register Address
const char HOUR     = 0x02;     // 0x01 is the Hours Register Address
const char TIMEZONE = 2;        // +02H00 GMT (South Africa)

// define pins
const int LEDS[]    =  {21, 22, 23, 25, 7, 2, 3, 4, 5, 6, 1}; // WiringPi Numbering Scheme
const int HOURS[]   =  {21, 22, 23, 25};                      // H0-H3
const int MINUTES[] =  {7, 2, 3, 4, 5, 6};                    // M0-M5
 
const int SECONDS   = 1;                                      // PWM Pin     
const int BTNS[]    = {26, 27};                               // B0-B1 for user input