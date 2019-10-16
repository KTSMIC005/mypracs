#ifndef STMCOMMS
#define STMCOMMS

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define  GET_RTC_TIME_CODE      0x00
#define  GET_SYS_TIME_CODE      0x01
#define  GET_HUMIDITY_CODE      0x02
#define  GET_TEMPERATURE_CODE   0x03
#define  GET_LDR_CODE           0x04
#define  GET_DAC_CODE           0x05
#define  GET_ALARM_CODE         0x06
#define  SEND_RTC_TIME_CODE     0x07

typedef struct {
  char seconds;
  char minutes;
  char hours;
} Time;

void STMCommsInit(void);

Time  getRTCTime(void);
Time  getSysTime(void);
float getHumidity(void);
float getTemperature(void);
float getLDR(void);
float getDAC(void);
bool  getAlarm(void);

void sendRTCTime(Time);
void setCurrentTime(void);

#include "STMComms.cpp"
#endif