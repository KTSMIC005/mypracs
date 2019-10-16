/*
*   Embedded Systems 2
*   Mini Prac A
*   Greenhouse logging software
*   
*   Members:
*   Michael Katsoulis   KTSMIC005
*   Lawrence Stanton    STNLAW003
*
*
*/

// -------------------------------------------------------------------------
// Includes
// -------------------------------------------------------------------------

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "MainApp.h"
#include <wiringSerial.h> 
#include <string>
// #include <BlynkApiWiringPi.h>
#include "STMComms.h"

// ------------------------------------------------------------------------
// Blynk Setup
// ------------------------------------------------------------------------

//#define BLYNK_DEBUG
// #define BLYNK_PRINT stdout
#ifdef RASPBERRY
  #include <BlynkApiWiringPi.h>
#else
  #include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

static const char *auth, *serv;
static uint16_t port;

#include <BlynkWidgets.h>

WidgetLED alarm_led(alarmVPin);
WidgetTerminal terminal(terminalVPin);

// make clean
// make target=raspberry
// sudo ./blynk --token=wR0WUwgv87bNmhupF8M7w39LhfJ9R5lF

// ------------------------------------------------------------------------

// -------------------------------------------------------------------------
// Global Variables
// ------------------------------------------------------------------------
// For real time section:
Time rtcTime, sysTime;
unsigned int samplingRate = 1;
// ------------------------------------------------------------------------
unsigned int setup    = 0;
unsigned int lightVal = 0;
unsigned int humidVal = 0;
float tempVal = 0.7;
float vOutVal = 0;

bool alarm_state = false;

unsigned long last_changeSamplingRate = 0;
unsigned long last_startStopLogging = 0;
bool logging = true;
static const unsigned int debounceTime = 200;

// ------------------------------------------------------------------------
// Functions 
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Blynk functions
// ------------------------------------------------------------------------

void blynkSetup()
{
    Blynk.begin(auth, serv, port);
}
void loop()
{
    Blynk.run();
    
}

void sendToApp(int pinNum, float f_val, int i_val){
    if (i_val >=0){
        // send -1 on the int if you want to write a float
        // else send int val
        Blynk.virtualWrite(pinNum, i_val);
    }else{
        Blynk.virtualWrite(pinNum, f_val);
    }
    

}

BLYNK_WRITE(V4)
{
    // for a value written in the blynk app.
    switch (param[0].asInt())
    {
    case 1:
        /* Param 0 means 1 sec sampling rate */
        samplingRate = 1;        
        break;
    case 2:
        /* Param 1 means 2 sec sampling rate */
        samplingRate = 2;
        break;
    case 3:
        /* Param 2 means 5 sec sampling rate */
        samplingRate = 5;           
        break;
  
    }
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("Sampling rate set to %is\n", samplingRate);
    printf("---------------------------------------------------------------------------------------------------------\n");
    char toWrite[100];
    sprintf(toWrite, "Sampling rate set to %is\n", samplingRate);
    terminal.write(toWrite, strlen(toWrite));
}

void resetTerminal(){
  fputs("\033c",stdout);
  printf("---------------------------------------------------------------------------------------------------------\n");
  printf("|RTC Time\t|Sys Time\t|Humidity\t|Temp\t\t|Light\t\t|DAC Out\t|Alarm\t|\n");
  printf("---------------------------------------------------------------------------------------------------------\n");
  terminal.clear();
}

void changeSampleRate(void){
  if(millis() - last_changeSamplingRate > debounceTime){   // Debounce
        last_changeSamplingRate = millis();

        switch (samplingRate){
          case 1:
            samplingRate = 2;
            break;
          case 2:
            samplingRate = 5;
            break;
          default:
            samplingRate = 1;
            break;
        }
        printf("---------------------------------------------------------------------------------------------------------\n");
        printf("Sample Speed changed to %i s/sample.\n", samplingRate);
        printf("---------------------------------------------------------------------------------------------------------\n");
        char toWrite[100];
        sprintf(toWrite, "Sample Speed changed to %i s/sample.\n", samplingRate);
        terminal.write(toWrite, strlen(toWrite));
  }
}

void stopStartLogging(void){
  if(millis() - last_startStopLogging > debounceTime){
    last_startStopLogging = millis();

    logging = !logging;

    if(logging){
      printf("Starting logging\n");
      printf("---------------------------------------------------------------------------------------------------------\n");
      printf("|RTC Time\t|Sys Time\t|Humidity\t|Temp\t\t|Light\t\t|DAC Out\t|Alarm\t|\n");
      printf("---------------------------------------------------------------------------------------------------------\n");
      char toWrite[100];
      sprintf(toWrite, "Starting logging\n");
      terminal.write(toWrite, strlen(toWrite));
    }else{
      printf("---------------------------------------------------------------------------------------------------------\n");
      printf("Stopping logging\n");
      printf("---------------------------------------------------------------------------------------------------------\n");
      char toWrite[100];
      sprintf(toWrite, "Stopping logging\n");
      terminal.write(toWrite, strlen(toWrite));
    }
  }
}

void getTemp(void){
  tempVal = getTemperature();
}

void getHumidityVal(void){
  float hum = getHumidity();        // Fetch from uart
  humidVal = (int) (hum*1023/3.3); 
}

void getLight(void){
  float li = getLDR();              // Fetch from uart
  lightVal = (int) (li*1023/3.3); 
}

void getVout(void){
  vOutVal =  getDAC();
}

void getAlarmState(void){
  bool temp = getAlarm();

  // Check for alarm dismissal.
  if( !temp && alarm_state && ((vOutVal > 2.65 || vOutVal < 0.65)) ){   // If alarm off, previous state yet valid alarm conditions
      printf("---------------------------------------------------------------------------------------------------------\n");
      printf("Alarm Dismissed.\n");
      printf("---------------------------------------------------------------------------------------------------------\n");
      char toWrite[100];
      sprintf(toWrite, "Alarm Dismissed.\n");
      terminal.write(toWrite, strlen(toWrite));
  }

  alarm_state = temp;
  if (getAlarm){
    alarm_led.on();
  } else{
    alarm_led.off();
  }
}

void getSystemTime(void){
  Time tmpTime = getSysTime();
 
  // If time is less than previous time,
  if((tmpTime.hours*60*60 + tmpTime.minutes*60 + tmpTime.seconds) < 
     (sysTime.hours*60*60 + sysTime.minutes*60 + sysTime.seconds)){
    // terminal.clear();
    resetTerminal();
    // terminal.println(TerminalHeader);
  }

  sysTime = tmpTime;
}

void getRealTime(void){
  rtcTime = getRTCTime();
}

void updateBlynk(void){
  // Get sensor Values
  getTemp();
  getHumidityVal();
  getVout();
  getLight(); 
  getSystemTime(); 
  getRealTime();
  getAlarmState();
  
  // Updating the blynk value for temperature
  Blynk.virtualWrite(tempVPin, tempVal);
  // Updating the blynk value for light
  Blynk.virtualWrite(lightVPin, lightVal ); // 0-1023
  // Updating the blynk value for humidity
  Blynk.virtualWrite(humidityVPin, humidVal ); //0-1023
  // Updating the blynk value for Vout
  Blynk.virtualWrite(VoutVPin, vOutVal ); //0-1023
  // updating the segmented switch for sample rate
  Blynk.virtualWrite(SamplingRateVPin, samplingRate); 
  
  printf("|%ih %im %is\t|", rtcTime.hours, rtcTime.minutes, rtcTime.seconds);
  printf("%ih %im %is\t|",  sysTime.hours, sysTime.minutes, sysTime.seconds);

  printf("%i humid\t| %.2f C\t| %i lum  \t| %.2f V\t| ",humidVal, tempVal, lightVal, vOutVal);
  
  char tmp = ' ';
  if(alarm_state){
    printf("  *");
    tmp = '*';
  }
  else{
    printf("   ");
  }
  printf("\t|\n");
  

  char toWrite[120];
  sprintf(toWrite, "|%ih%im%i\t|%ih%im%i|%ihum\n|%.2fC\t| %ilum\t|%.2fV\t|%c\t|\n", rtcTime.hours,
                    rtcTime.minutes, rtcTime.seconds, sysTime.hours, sysTime.minutes, sysTime.seconds,
                    humidVal, tempVal, lightVal, vOutVal, tmp);
  terminal.write(toWrite, strlen(toWrite));

}



// ------------------------------------------------------------------------
// Main
// ------------------------------------------------------------------------

void initGPIO(void){
 
    printf("Setting up GPIO....\n");

    // Setups
    STMCommsInit();    
    printf("Setup UART\n ");
    setCurrentTime();
    wiringPiSetup();
    //set as inputs
    pinMode(samplingRateBtn, INPUT);
    pullUpDnControl(samplingRateBtn, PUD_UP);
    pinMode(startStopLoggingBtn, INPUT);
    pullUpDnControl(startStopLoggingBtn, PUD_UP);

    wiringPiISR(samplingRateBtn, INT_EDGE_FALLING, &changeSampleRate);
    wiringPiISR(startStopLoggingBtn, INT_EDGE_FALLING, &stopStartLogging);
    printf("inputs set up.\n");
    blynkSetup();
    printf("Setup Blynk\n");
    

    setup = 1;
}
// ------------------------------------------------------------------------



int main(int argc, char* argv[])
{
    parse_options(argc, argv, auth, serv, port);


    printf("Now running the main:....\n");
    initGPIO();

    printf("Time is set\n");

    resetTerminal();
    while(true){           
      if(logging){
        loop();
        updateBlynk();
      }

      terminal.flush();
      
		  delay(1000*samplingRate); 											
	}
	return 0;
}