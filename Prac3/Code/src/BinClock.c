/*
 * Student Numbers: KTSMIC005 STNLAW003
 * Date: 13 August 2019
*/

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
#include <signal.h>

#include "BinClock.h"
#include "CurrentTime.h"

// Global variables
int hours, mins, secs;
long lastInterruptTime = 0; // Used for button debounce
int debounce = 200;			// Debounce Time (ms)
int RTC;					// Real Time Clock

int HH, MM, SS;

void initGPIO(void) {
	printf("Running initGPIO().\n");
	wiringPiSetup(); 											// Defaulted to WiringPI Pin Numbering

	RTC = wiringPiI2CSetup(RTCAddr); 							// Set up the RTC
																// Set up each LED to Output
	for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++) {
		pinMode(LEDS[i], OUTPUT);
	}
																
											// Special case for PWM on Seconds LED
	softPwmCreate(SECONDS, 0, 60); 									// (pin, initial, range)

	printf("Completed LED setup.\n");
																// Set up the Buttons to input with PUR
	for (int j = 0 ; j < sizeof(BTNS) / sizeof(BTNS[0]) ; j++) {
		pinMode(BTNS[j], INPUT);
		pullUpDnControl(BTNS[j], PUD_UP);
	}
																// Attach interrupts to Buttons
	wiringPiISR(BTNS[1], INT_EDGE_FALLING, &hourIncrement);
	wiringPiISR(BTNS[0], INT_EDGE_FALLING, &minuteIncrement);

	printf("Completed Push Button setup.\n");
	printf("Completed Setup.\n");
}

int main(void) {
	signal(SIGINT, cleanup);									//Catch Ctrl-c

	printf("Running main().\n");
	initGPIO();

	setCurrentTime();

	for (;;) {													// Main recursive loop
		fputs("\033c", stdout);									// Clear the print buffer
																// INPUT
		hours = wiringPiI2CReadReg8(RTC, HOUR); 					// Read the HOUR register from RTC
		printf("Read %x hours.\n", hours);

		mins = wiringPiI2CReadReg8(RTC, MIN); 						// Read the MIN register from RTC
		printf("Read %x minutes.\n", mins);

		secs = (wiringPiI2CReadReg8(RTC, SEC) & (~0x80)); 			// Read the SEC register from RTC
		printf("Read %x seconds.\n", secs);

																	// Convert to decimal values
		hours 	= hexCompensation(hours);
		mins 	= hexCompensation(mins);
		secs	= hexCompensation(secs);
		printf("Time Check: %d:%d:%d\n", hours, mins, secs);
																// OUTPUT
		lightHours(hours); 											// Update Hours LED Output
		printf("Updated LED's for Hours.\n");
																	// Update Minutes LED Output
		lightMins(mins);
		printf("Updated LED's for Minutes.\n");						

		secPWM(secs); 												// Update Seconds PWM

		printf("Current Read Time: %d:%d:%d\n", hours, mins, secs);

		delay(100); 												//100ms delay for stability
	}
	return 0;
}

/*
 * Change the hour format to 12 hours
 */
int hours12Format(int hours) {
	return (hours % 12);
}

/*
 * Turns on corresponding LED's for hours
 */
void lightHours(int hours) {
	for (int i = 3; i >= 0; i--) {						// Decrease through 4 LED's
		if (hours % 2) {								// If binary 1
			digitalWrite(HOURS[i], HIGH);
			printf("Hours[%d] (Pin %d) HIGH.\n", i, HOURS[i]);
		}
		else {											// If binary 0
			digitalWrite(HOURS[i], LOW);
			printf("Hours[%d] (Pin %d) LOW.\n", i, HOURS[i]);
		}
		hours /= 2;
	}													// Move to next binary digit
}

/*
 * Update the Minute LEDs
 */
void lightMins(int minutes) {
	for (int i = 5; i >= 0; i--) {						// Decrease through the 6 LED's
		if (minutes % 2) {								// If binary 1
			digitalWrite(MINUTES[i], HIGH);
			printf("Minutes[%d] (Pin %d) HIGH.\n", i, MINUTES[i]);
		}
		else {											// If binary 0
			digitalWrite(MINUTES[i], LOW);
			printf("Minutes[%d] (Pin %d) LOW.\n", i, MINUTES[i]);
		}
		minutes /= 2;									// Move to next binary digit
	}
}

/*
 * PWM on the Seconds LED
 * The LED should have 60 brightness levels
 * The LED should be "off" at 0 seconds, and fully bright at 59 seconds
 */
void secPWM(int seconds){
	seconds %= 60;										// Configured to 60 (60 seconds) range
	softPwmWrite(SECONDS, seconds);						// Pass on PWM command
}

//Converts from Hexidecimal to Decimal format for reading from I2C
int hexCompensation(int units){
	int unitsU = units % 0x10;

	if (units >= 0x50) {
		units = 50 + unitsU;
	}
	else if (units >= 0x40) {
		units = 40 + unitsU;
	}
	else if (units >= 0x30) {
		units = 30 + unitsU;
	}
	else if (units >= 0x20) {
		units = 20 + unitsU;
	}
	else if (units >= 0x10) {
		units = 10 + unitsU;
	}
	return units;
}

//Converts from Decimal to hexidecimal format for writing to I2C
int decCompensation(int units){
	int unitsU = units % 10;

	if (units >= 50) {
		units = 0x50 + unitsU;
	}
	else if (units >= 40) {
		units = 0x40 + unitsU;
	}
	else if (units >= 30) {
		units = 0x30 + unitsU;
	}
	else if (units >= 20) {
		units = 0x20 + unitsU;
	}
	else if (units >= 10) {
		units = 0x10 + unitsU;
	}
	return units;
}

/*
 * hourIncrement
 * Fetch the hour value off the RTC, increase it by 1, and write back
 */
void hourIncrement(void){
	long interruptTime = millis();									//Debounce

	if (interruptTime - lastInterruptTime > debounce) {
		lastInterruptTime = interruptTime;
		printf("Interrupt 1 triggered, %x\n", hours);

		hours = hexCompensation(wiringPiI2CReadReg8(RTC, HOUR)); 	// Read the HOUR register from RTC

		hours++;
		hours %= 12;
		wiringPiI2CWriteReg8(RTC, HOUR, decCompensation(hours));	// Write the updated time back to RTC
	}
}

/* 
 * minuteIncrement
 * Fetch the minute value off the RTC, increase it by 1, and write back
 */
void minuteIncrement(void){
	long interruptTime = millis();									// Debounce

	if (interruptTime - lastInterruptTime > debounce){
		lastInterruptTime = interruptTime;
		printf("Interrupt 2 triggered, %x\n", mins);

		mins = hexCompensation(wiringPiI2CReadReg8(RTC, MIN)); 		// Read the MIN register from RTC

		mins++;
		mins %= 60;
		wiringPiI2CWriteReg8(RTC, MIN, decCompensation(mins));		// Write updated time back to MIN
	}
}

/* 
 * Update the RTC to the system time
 */
void setCurrentTime(){
		HH = getHours();
		MM = getMins();
		SS = getSecs();

		HH = hours12Format(HH);
		HH = decCompensation(HH);
		wiringPiI2CWriteReg8(RTC, HOUR, HH);

		MM = decCompensation(MM);
		wiringPiI2CWriteReg8(RTC, MIN, MM);

		SS = decCompensation(SS);
		wiringPiI2CWriteReg8(RTC, SEC, 0x80 + SS);			// Maintain the 1st Oscilator bit (0x80)
}

void cleanup(int i){
																	// Set all outputs to LOW
	for(int i=0 ; i < sizeof(LEDS) / sizeof(LEDS[0]) ; i++){
		digitalWrite(LEDS[i], LOW);
	}
																	// Set up each LED to Input (High Impedance)
	for (int i = 0 ; i < sizeof(LEDS) / sizeof(LEDS[0]); i++) {
		pinMode(LEDS[i], INPUT);
	}
	printf("Cleaned up.\n");
	exit(0);
}