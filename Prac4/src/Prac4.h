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
                                                    // Define buttons
#define PAUSE_BUTTON    18                            
#define STOP_BUTTON     23
#define BTNS            [PAUSE_BUTTON, STOP_BUTTON]
                                                    //Define LEDS
#define PAUSE_LED       22
#define STOP_LED        27
#define LEDS            [PAUSE_LED, STOP_LED]

#define BUFFER_SIZE     1000
                                                    // SPI Settings
#define SPI_CHAN        0
#define SPI_SPEED                                       // TODO

#define FILENAME "src/sound_16k_8bit.raw"           // Sound file name

                                                    //Function definitions
void play_audio(void);
void stop_audio(void);
int setup_gpio(void);
int main(void);

#endif
