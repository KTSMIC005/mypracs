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

const int BUFFER_SIZE     = 1000;
                                                    // SPI Settings
const int SPI_CHAN        = 0;
//const int SPI_SPEED                                       // TODO

#define FILENAME "src/sound_16k_8bit.raw"           // Sound file name

                                                    //Function definitions
void play_audio(void);
void stop_audio(void);
int setup_gpio(void);
int main(void);
void cleanup(int);

#endif