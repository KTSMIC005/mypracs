/*
 * Student Numbers: KTSMIC005 STNLAW003
 * Date: 13 August 2019
*/

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

#include "BinClock.h"
#include "CurrentTime.h"

//static int b_write =0b11011110;
//static int b_read = 0b11011111;

// Global variables
int hours, mins, secs;
long lastInterruptTime = 0; // Used for button debounce
int debounce = 200;			// Debounce Time (ms)
int RTC;					// Real Time Clock

int HH, MM, SS;

void initGPIO(void)
{
	printf("Running initGPIO().\n");
	wiringPiSetup(); // Defaulted to WiringPI Pin Numbering

	RTC = wiringPiI2CSetup(RTCAddr); // Set up the RTC

	// Set up each LED to Output
	for (int i; i < sizeof(LEDS) / sizeof(LEDS[0]); i++)
	{
		pinMode(LEDS[i], OUTPUT);
	}

	// Special case for PWM on Seconds LED
	pinMode(SEC, OUTPUT);
	softPwmCreate(SEC, 0, 60); // (pin, initial, range)

	printf("Completed LED setup.\n");

	// Set up the Buttons
	for (int j; j < sizeof(BTNS) / sizeof(BTNS[0]); j++)
	{
		pinMode(BTNS[j], INPUT);
		pullUpDnControl(BTNS[j], PUD_UP);
	}

	// Attach interrupts to Buttons
	wiringPiISR(BTNS[1], INT_EDGE_FALLING, &hourIncrement);
	wiringPiISR(BTNS[0], INT_EDGE_FALLING, &minuteIncrement);

	printf("Completed Push Button setup.\n");
	printf("Completed Setup.\n");
}

int main(void)
{
	printf("Running main().\n");
	initGPIO();

	// Set random time (3:04PM)
	wiringPiI2CWriteReg8(RTC, HOUR, 0x13 + TIMEZONE);
	wiringPiI2CWriteReg8(RTC, MIN, 0x4);
	wiringPiI2CWriteReg8(RTC, SEC, 0x80);

	// Main recursive loop
	for (;;)
	{
		// INPUT
		hours = wiringPiI2CReadReg8(RTC, HOUR); // Read the HOUR register from RTC
		printf("Read %d hours.\n", hours);

		mins = wiringPiI2CReadReg8(RTC, MIN); // Read the MIN register from RTC
		printf("Read %d minutes.\n", mins);

		secs = (wiringPiI2CReadReg8(RTC, SEC) & (~0x80)); // Read the SEC register from RTC
		printf("Read %d seconds.\n", secs);

		// OUTPUT
		lightHours(hours); // Update Hours LED Output
		printf("Updated LED's for Hours.\n");

		lightMins(mins);
		printf("Updated LED's for Minutes."); // Update Minutes LED Output

		secPWM(secs); // Update Seconds PWM

		printf("Current Read Time: %x:%x:%x\n", hours, mins, secs);

		delay(100); //100ms delay for stability
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
void lightHours(int hours){
	for (int i = 3; i >= 0; i--) {						// Decrease through 4 LED's
		if (hours % 2) {								// If binary 1
			digitalWrite(HOURS[i], HIGH);
		}
		else {											// If binary 0
			digitalWrite(HOURS[i], LOW);
		}
	hours = hours / 2;
	}													// Move to next binary digit
}

/*
 * Update the Minute LEDs
 */
void lightMins(int minutes) {
	for (int i = 4; i >= 0; i--) {						// Decrease through the 5 LED's
		if (minutes % 2) {								// If binary 1
			digitalWrite(MINUTES[i], HIGH);
		}
		else {											// If binary 0
			digitalWrite(MINUTES[i], LOW);
		}
		minutes = minutes / 2;							// Move to next binary digit
	}
}

/*
 * PWM on the Seconds LED
 * The LED should have 60 brightness levels
 * The LED should be "off" at 0 seconds, and fully bright at 59 seconds
 */
void secPWM(int seconds){
	if (seconds > 59)												// Configured to 60 (60 seconds) range
	{
		seconds -= 60;
		printf("Seconds were above 59, reducing to %d", seconds);
	}
	softPwmWrite(SEC, seconds);										// Pass on PWM command
}

/*
 * hexCompensation
 * This function may not be necessary if you use bit-shifting rather than decimal checking for writing out time values
 */
int hexCompensation(int units){
	/*Convert HEX or BCD value to DEC where 0x45 == 0d45 
	  This was created as the lighXXX functions which determine what GPIO pin to set HIGH/LOW
	  perform operations which work in base10 and not base16 (incorrect logic) 
	*/
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

/*
 * decCompensation
 * This function "undoes" hexCompensation in order to write the correct base 16 value through I2C
 */
int decCompensation(int units){
	int unitsU = units % 10;

	if (units >= 50)
	{
		units = 0x50 + unitsU;
	}
	else if (units >= 40)
	{
		units = 0x40 + unitsU;
	}
	else if (units >= 30)
	{
		units = 0x30 + unitsU;
	}
	else if (units >= 20)
	{
		units = 0x20 + unitsU;
	}
	else if (units >= 10)
	{
		units = 0x10 + unitsU;
	}
	return units;
}

/*
 * hourIncrement
 * Fetch the hour value off the RTC, increase it by 1, and write back
 * Be sure to cater for there only being 23 hours in a day
 * Software Debouncing should be used
 */
void hourIncrement(void){
	//Debounce
	long interruptTime = millis();

	if (interruptTime - lastInterruptTime > debounce)
	{
		printf("Interrupt 1 triggered, %x\n", hours);
		//Fetch RTC Time
		//Increase hours by 1, ensuring not to overflow
		//Write hours back to the RTC

		hours++;
		if (hours > 12)
		{
			hours -= 12;
		}
		wiringPiI2CWriteReg8(RTC, HOUR, hours);
		lastInterruptTime = interruptTime;
	}
}

/* 
 * minuteIncrement
 * Fetch the minute value off the RTC, increase it by 1, and write back
 */
void minuteIncrement(void){
	long interruptTime = millis();

	if (interruptTime - lastInterruptTime > debounce)
	{
		printf("Interrupt 2 triggered, %x\n", mins);
		//Fetch RTC Time
		//Increase minutes by 1, ensuring not to overflow
		//Write minutes back to the RTC

		mins++;
		if (mins > 60)
		{
			mins -= 60;
		}
		wiringPiI2CWriteReg8(RTC, MIN, 0x4);
		lastInterruptTime = interruptTime;
	}
}

//This interrupt will fetch current time from another script and write it to the clock registers
//This functions will toggle a flag that is checked in main
void toggleTime(void)
{
	long interruptTime = millis();

	if (interruptTime - lastInterruptTime > debounce)
	{
		HH = getHours();
		MM = getMins();
		SS = getSecs();

		HH = hours12Format(HH);
		HH = decCompensation(HH);
		wiringPiI2CWriteReg8(RTC, HOUR, HH);

		MM = decCompensation(MM);
		wiringPiI2CWriteReg8(RTC, MIN, MM);

		SS = decCompensation(SS);
		wiringPiI2CWriteReg8(RTC, SEC, 0b10000000 + SS);
	}
	lastInterruptTime = interruptTime;
}
