#include "Prac4.h"

using namespace std;

bool playing = true;                        // Set false when paused
bool stopped = false;                       // Set true to close program
unsigned char buffer[2][BUFFER_SIZE][2];
int buffer_location = 0;
bool bufferReading = 0;                     // Using to switch between column 0 and 1 - the first column
bool threadReady = false;                   // Using to finish writing the first column at the start of the song, before the column is played

                                            // Interrupts.
                                            // Don't forget to use debouncing.
void play_pause_isr(void){
                                            // TODO
}

void stop_isr(void){
                                            // TODO
}
                                            
int setup_gpio(void){                      // Setup Function. Called once.
    
    wiringPiSetup();                        // Set up WiringPi
                                            // TODO set up buttons
                                            // TODO set up the SPI interface
    return 0;
}

/* 
 * Thread that handles writing to SPI
 * 
 * You must pause writing to SPI if not playing is true (the player is paused)
 * When calling the function to write to SPI, take note of the last argument.
 * You don't need to use the returned value from the wiring pi SPI function
 * You need to use the buffer_location variable to check when you need to switch buffers
 */
void *playThread(void *threadargs){
    while(!threadReady)                     // Wait until tread ready
        continue;
    
    while(!stopped){                        // Only play if not stopped
		                                    // TODO Suspend playing if paused
                                            // TODO Write the buffer out to SPI
		
        //Do some maths to check if you need to toggle buffers
        buffer_location++;
        if(buffer_location >= BUFFER_SIZE) {
            buffer_location = 0;
            bufferReading = !bufferReading; // switches column one it finishes one column
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
    pthread_attr_getschedparam (&tattr, &param);                /* safe to get existing scheduling param */
    param.sched_priority = newprio;                             /* set the priority; others are unchanged */
    pthread_attr_setschedparam (&tattr, &param);                /* setting the new scheduling param */
    pthread_create(&thread_id, &tattr, playThread, (void *)1);  /* with new priority specified *
    
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
        while( (threadReady && bufferWriting) == (bufferReading && counter) == 0){
                                                                                    // Wait until after it has written to a side,
            continue;                                                               // and the thread is still reading from the other side
        }
                                                                                    //Set config bits for first 8 bit packet and OR with upper bits
        buffer[bufferWriting][counter][0] = ;                                           //TODO
                                                                                    //Set next 8 bit packet
        buffer[bufferWriting][counter][1] = ;                                           //TODO
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
    return 0;
}