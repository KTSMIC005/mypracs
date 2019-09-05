#include "Prac4.h"

using namespace std;

bool            playing         = true;                     // Set false when paused
bool            stopped         = false;                    // Set true to close program
unsigned char   buffer[2][BUFFER_SIZE][2];                  // [bufferReading][bufferLocation][]
int             bufferLocation  = 0;
bool            bufferReading   = 0;                        // Using to switch between column 0 and 1 - the first column
bool            threadReady     = false;                    // Using to finish writing the first column before playback

                                                            // Interrupts. Use hardware debouncing
void play_pause_isr(void){
    playing = !playing;
    digitalWrite(PAUSE_BUTTON, playing);
}

void stop_isr(void){
    stopped = true;
    digitalWrite(STOP_LED, HIGH);
}

bool setup = false;                                            
int setup_gpio(void){                                               // Setup Function. Called once.
    if(setup)                                                       // Prevent multiple setups
        return 0;
    
    printf("Running init_gpio().\n");
    wiringPiSetup();                                                // Set up WiringPi
                                                                    
   	for (int j = 0 ; j < sizeof(BTNS) / sizeof(BTNS[0]) ; j++) {    // Set up Buttons
		pinMode(BTNS[j], INPUT);
		pullUpDnControl(BTNS[j], PUD_DOWN);                         // PDR for Op-Amp to push
	}

    wiringPiISR(PAUSE_BUTTON,   INT_EDGE_FALLING, &play_pause_isr);
	wiringPiISR(STOP_BUTTON,    INT_EDGE_FALLING, &stop_isr);

                                                                    //Set up LEDs
    for(int i=0; i<(sizeof(LEDS)/sizeof(LEDS[0])); i++)){
        pinMode(LEDS[i], OUTPUT);
    }
                                                                    // TODO set up the SPI interface
    
    setup = true;
    return 0;
}
                                                        /* 
                                                        * Thread that handles writing to SPI
                                                        * 
                                                        * You must pause writing to SPI if not playing is true (the player is paused)
                                                        * When calling the function to write to SPI, take note of the last argument.
                                                        * You don't need to use the returned value from the wiring pi SPI function
                                                        * You need to use the bufferLocation variable to check when you need to switch buffers
                                                        */
void *playThread(void *threadargs){
    while(!threadReady)                                             // Wait until tread ready
        continue;
    
    while(!stopped){                                                // Only play if not stopped
		while(!playing)                                             // Suspend playing if paused
            delay(50);                                  
                                                                    // TODO Write the buffer out to SPI
		
                                                                    // Check if toggle buffers needed
        bufferLocation++;
        if(bufferLocation >= BUFFER_SIZE) {
            bufferLocation = 0;
            bufferReading = !bufferReading;                         // Switches column once it finishes current column
        }
    }
    pthread_exit(NULL);
}

int main(){
    if(setup_gpio()==-1){                                           // Call the setup_gpio function
        return 0;
    }
                                                                    /* Initialize thread with parameters
                                                                    * Set the play thread to have a 99 priority
                                                                    * Read https://docs.oracle.com/cd/E19455-01/806-5257/attrib-16/index.html
                                                                    */ 
	pthread_attr_t tattr;
    pthread_t thread_id;
    int newprio = 99;
    sched_param param;
    
    pthread_attr_init (&tattr);
    pthread_attr_getschedparam (&tattr, &param);                    /* safe to get existing scheduling param */
    param.sched_priority = newprio;                                 /* set the priority; others are unchanged */
    pthread_attr_setschedparam (&tattr, &param);                    /* setting the new scheduling param */
    pthread_create(&thread_id, &tattr, playThread, (void *)1);      /* with new priority specified *
    
                                                                /*
                                                                * Read from the file, character by character
                                                                * You need to perform two operations for each character read from the file
                                                                * You will require bit shifting
                                                                * 
                                                                * buffer[bufferWriting][counter][0] needs to be set with the control bits
                                                                * as well as the first few bits of audio
                                                                * 
                                                                * buffer[bufferWriting][counter][1] needs to be set with the last audio bits
                                                                * 
                                                                * Don't forget to check if you have pause set or not when writing to the buffer
                                                                * 
                                                                */
                                                                
    char ch;
    FILE *filePointer;
    printf("%s\n", FILENAME);                                   // Opening FILENAME
    filePointer = fopen(FILENAME, "r");                         // Open in Read mode

    if (filePointer == NULL) {                                  // If file not found
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int counter = 0;
    int bufferWriting = 0;

                                                                
	 while( (ch = fgetc(filePointer)) != EOF){                                      // Loop to read from the file
        while( threadReady && bufferWriting == bufferReading && counter == 0){
                                                                                    // Wait until after it has written to a side,
            continue;                                                               // and the thread is still reading from the other side
        }
                                                                                    //Set config bits for first 8 bit packet and OR with upper bits (bits 0-7)
        buffer[bufferWriting][counter][0] = ;                                           //TODO
                                                                                    //Set next 8 bit packet (bits 8-15)
        buffer[bufferWriting][counter][1] = ;                                           //TODO
        printf("Saved to Buffer:\t%s\t%s", buffer[bufferWriting][counter][0], buffer[bufferWriting][counter][1])
        counter++;
        if(counter >= BUFFER_SIZE+1){
            if(!threadReady){
                threadReady = true;
            }
            counter = 0;
            bufferWriting = (bufferWriting+1) % 2;
        }

    }
                                                                                    
    fclose(filePointer);                               // Close the file
    printf("Complete reading");	 
                                                                                    
	pthread_join(thread_id, NULL);                     // Join and exit the playthread
    pthread_exit(NULL);

    digitalWrite(STOP_BUTTON, HIGH);
    return 0;
}