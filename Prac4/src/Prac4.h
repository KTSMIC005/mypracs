#ifndef PRAC4_H
#define PRAC4_H
                                                    // Includes
#include <wiringPi.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <iostream>
#include <signal.h>
                                                    // Define buttons
const int PAUSE_BUTTON    = 18;                            
const int STOP_BUTTON     = 23;
const int BTNS[]          = {18, 23};
                                                    //Define LEDS
const int PAUSE_LED       = 22;
const int STOP_LED        = 27;
const int LEDS[]          = {22, 27};

                                                    // Sound file details
#define FILENAME "src/sound_16k_8bit.raw"
#define SAMPLE_RATE         16000
const int BUFFER_SIZE     = 1000;
                                                    // SPI Settings
#define SPI_CHAN            0
#define SPI_MODE            0

#define CHANNELS            1
#define WIDTH               16

const int compensator     = 8/5;

const int SPI_SPEED       = SAMPLE_RATE*WIDTH*CHANNELS*compensator;                                         // TODO

                                                    // MCP4911 Config Bits
#define BUFFER              0b0100
#define GAIN                0b0010
#define SHUTDOWN            0b0001

                                                    //Function definitions
void play_audio(void);
void stop_audio(void);
int setup_gpio(void);
int main(void);
void cleanup(int);

#endif