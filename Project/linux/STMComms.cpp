#include "STMComms.h"

static int fd;

void STMCommsInit(){
  fd = serialOpen("/dev/ttyS0", 9600);
}

Time getRTCTime(){
  Time t;
  
  serialPutchar(fd, GET_RTC_TIME_CODE);
  char echo = serialGetchar(fd);
  
  if(echo == GET_RTC_TIME_CODE){
    t.seconds = serialGetchar(fd);
    t.minutes = serialGetchar(fd);
    t.hours   = serialGetchar(fd);
    return t;
  }
  else{
    delay(10);
    return getRTCTime();
  }
}

Time getSysTime(){
  Time t;
  
  serialPutchar(fd, GET_SYS_TIME_CODE);
  char echo = serialGetchar(fd);
  
  if(echo == GET_SYS_TIME_CODE){
    t.seconds = serialGetchar(fd);
    t.minutes = serialGetchar(fd);
    t.hours   = serialGetchar(fd);
    return t;
  }
  else{
    delay(10);
    return getRTCTime();
  }
}

float getHumidity(){
  float V;
  char n;

  serialPutchar(fd, GET_HUMIDITY_CODE);
  char echo = serialGetchar(fd);

  if(echo == GET_HUMIDITY_CODE){
    n = serialGetchar(fd);
    V = (float)(n * (3.3 / 0xFF));
    return V;
  }
  else{
    delay(10);
    return getHumidity();
  }
}

float getTemperature(){
  float T;
  char n;

  serialPutchar(fd, GET_TEMPERATURE_CODE);
  char echo = serialGetchar(fd);

  if(echo == GET_TEMPERATURE_CODE){
    n = serialGetchar(fd);
    T = (float)(n * 135.0/ 0xFF)  - 10.0;
    return T;
  }
  else{
    delay(10);
    return getTemperature();
  }
}

float getLDR(){
  float L;
  char n;

  serialPutchar(fd, GET_LDR_CODE);
  char echo = serialGetchar(fd);

  if(echo == GET_LDR_CODE){
    n = serialGetchar(fd);
    L = (float)(n * (3.3 / 0xFF));
    return L;
  }
  else{
    delay(10);
    return getLDR();
  }
}

float getDAC(){
  float V;
  char n;

  serialPutchar(fd, GET_DAC_CODE);
  char echo = serialGetchar(fd);

  if(echo == GET_DAC_CODE){
    n = serialGetchar(fd);
    V = (float)(n * (3.3 / 0xFF));
    return V;
  }
  else{
    delay(10);
    return getDAC();
  }
}

bool getAlarm(){
  char a;

  serialPutchar(fd, GET_ALARM_CODE);
  char echo = serialGetchar(fd);

  if(echo == GET_ALARM_CODE){
    a = serialGetchar(fd);
    return (bool)a;
  }
  else{
    delay(10);
    return getAlarm();
  }
}

void sendRTCTime(Time t){
  serialPutchar(fd, SEND_RTC_TIME_CODE);
  char echo = serialGetchar(fd);

  if(echo == SEND_RTC_TIME_CODE){
    serialPutchar(fd, t.seconds);
    serialPutchar(fd, t.minutes);
    serialPutchar(fd, t.hours);
  }
  else{             // Wait 10ms before trying again
    delay(10);
    sendRTCTime(t);
  }
}

void setCurrentTime(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  Time t = {
    .seconds = (char)timeinfo ->tm_sec,
    .minutes = (char)timeinfo ->tm_min,
    .hours   = (char)timeinfo ->tm_hour,
  };

  sendRTCTime(t);
  printf("Sent Time:\t%d:\t%d:\t%d\n", t.hours, t.minutes, t.seconds);
}