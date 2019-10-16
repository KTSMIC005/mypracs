#include <stdio.h>
#include <stdlib.h>

#include "STMComms.h"

void updateVariables(void);

Time rtcTime;
Time sysTime;
float H;
float T;
float L;
float D;
bool  a;


int main(void){
    wiringPiSetup();
    STMCommsInit();
    setCurrentTime();
    //float X;
    while(true){
        //updateVariables();
        //printf("%d\t:%d\t:%d\t%d\t:%d\t:%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\n", rtcTime.hours, rtcTime.minutes, rtcTime.seconds,
        //                                                                    sysTime.hours, sysTime.minutes, sysTime.seconds,
        //                                                                    H, T, L, D, a);
        
        //X = getTemperature();
        //printf("%.2f\n", X);
        a = getAlarm();
        printf("%d\n", a);
        delay(100);
    }
}
void updateVariables(){
    rtcTime = getRTCTime();
    sysTime = getSysTime();
    H = getHumidity();
    delay(50);
    T = getTemperature();
    delay(50);
    L = getLDR();
    delay(50);
    D = getDAC();
    delay(50);
    a = getAlarm();
}