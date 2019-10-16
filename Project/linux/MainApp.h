
// For RTC

#ifndef BINCLOCK_H
#define BINCLOCK_H
#endif


// ------------------------------------------------------------------------
// Function definitions
// ------------------------------------------------------------------------

// General Functions
void initGPIO(void);


// define pins
const int TXD = 15;
const int RXD = 16;

const int samplingRateBtn = 23;
const int startStopLoggingBtn = 24;

// virtual pins for blynk
const int tempVPin = 0;
const int humidityVPin = 1;
const int lightVPin = 2;
const int VoutVPin = 3;
const int SamplingRateVPin = 4;


const int alarmVPin = 5;
const int terminalVPin = 6;
