#include "Prac4.h"
#include "wiringPi.h"                                       //Used while programming in Windows, otherwise redundant
#include "wiringPiSPI.h"

using namespace std;

bool            playing         = true;                     // Set false when paused
bool            stopped         = false;                    // Set true to close program
unsigned char   buffer[2][BUFFER_SIZE][2];                  // [bufferReading][bufferLocation][]
int             bufferLocation  = 0;
int             bufferReading   = 0;                        // Using to switch between column 0 and 1 - the first column
bool            threadReady     = false;                    // Using to finish writing the first column before playback

                                                            // Interrupts. Use hardware debouncing
void play_pause_isr(void){
    playing = !playing;
    if(!playing){
        delay(1);
        wiringPiSPIDataRW(SPI_CHAN, (unsigned char*)PAUSE_STATE, sizeof(PAUSE_STATE));
    }   
    digitalWrite(PAUSE_LED, playing);
}

void stop_isr(void){
    stopped = true;
    cleanup(0);
}

bool setup = false;                                            
int setup_gpio(void){                                                           // Setup Function. Called once.
    if(setup)                                                                   // Prevent multiple setups
        return 0;
    
    printf("Running\tinit_gpio().\n");
    wiringPiSetupGpio();                                                        // Set up WiringPi
                                                                    
   	for (unsigned int j = 0 ; j < (sizeof(BTNS) / sizeof(BTNS[0])) ; j++) {     // Set up Buttons
		pinMode(BTNS[j], INPUT);
		pullUpDnControl(BTNS[j], PUD_DOWN);                                     // PDR for Op-Amp to push
	}

    printf("Buttons set to input.\n");

    wiringPiISR(PAUSE_BUTTON,   INT_EDGE_FALLING, &play_pause_isr);
	wiringPiISR(STOP_BUTTON,    INT_EDGE_FALLING, &stop_isr);

                                                                                //Set up LEDs
    for(unsigned int i=0 ; i < (sizeof(LEDS) / sizeof(LEDS[0])) ; i++){
        pinMode(LEDS[i], OUTPUT);
    }

    printf("LED's set to output.\n");
                                                                                // Set up the SPI interface
    if(wiringPiSPISetup(SPI_CHAN, SPI_SPEED) != -1){                            // Defaults to Mode 0
        printf("SPI Connected.\n");
    }
    else{
        printf("SPI Connection Failed.\n");
        return -1;
    }
    
    setup = true;
    printf("Finished\tinit_gpio().\n\n");
    return 0;
}

PI_THREAD (play_audio){
    while(!threadReady)                                                         // Wait until tread ready
        delay(1);
    
    digitalWrite(LDAC, LOW);
    while(!stopped){                                                            // Only play if not stopped
        while(!playing)                                                         // Suspend playing if paused
            delay(50); 
        
        
        //printf("Sending[%d][%d]:\t%X\t%X.\n",
        //    bufferReading,
        //    bufferLocation,
        //    buffer[bufferReading][bufferLocation][0],
        //    buffer[bufferReading][bufferLocation][1]);

        wiringPiSPIDataRW(SPI_CHAN, buffer[bufferReading][bufferLocation], 2);                                  // Manually added 2 for efficiency
            //sizeof(buffer[bufferReading][bufferLocation])/sizeof(buffer[bufferReading][bufferLocation][0]));
        

                                                                                // Check if toggle buffers needed
        
        bufferLocation++;
        piLock(0);
        if(bufferLocation >= BUFFER_SIZE) {
            bufferLocation = 0;
            bufferReading = (bufferReading+1) % 2;                              // Switches column once it finishes current column
            //wiringPiSPISetup(SPI_CHAN, SPI_SPEED);                               // Reset the speed
        }
        piUnlock(0);
    }
    printf("Exiting Thread.\n");
    return(0);
}

int main(){
    signal(SIGINT, cleanup);								    //Catch Ctrl-c
    
    digitalWrite(LDAC, HIGH);                                   // Prevent DAC from updating during setup.

    if(setup_gpio()==-1){                                       // Call the setup_gpio function
        return -1;
    }

    digitalWrite(PAUSE_LED  , HIGH);                            //By default indicate playing
    digitalWrite(STOP_LED, HIGH);

	piThreadCreate(play_audio);
                                                                
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

    char playConfig = 0*BUFFER + 1*GAIN + 1*SHUTDOWN;                               // Configure no Buffer on Vref, Gain 1, Don't Shutdown

    printf("\nPlaying...\n");                                                       
	while((ch = fgetc(filePointer)) != EOF){                                       // Loop to read from the file
        while( (bufferWriting==bufferReading) && threadReady && (counter==0)){
        delay(1);                                                                   // Wait until after it has written to a side,
                                                                                    // and the thread is still reading from the other side
        }
                                                                                    // Set config bits for first 8 bit packet and OR with upper bits (bits 0-7)
        buffer[bufferWriting][counter][0] = ch>>6;                                  // Add the first 2 bits of ch
        buffer[bufferWriting][counter][0] |=playConfig;                             // Add configuration bits (commented as config = 0)
                                                                                    
                                                                                    // Set next 8 bit packet (bits 8-15)
        buffer[bufferWriting][counter][1] = ch<<2;                                  // Add the last 6 bits, last two D.N.C.
        
        counter++;
        piLock(0);
        if(counter >= BUFFER_SIZE){
            if(!threadReady){
                threadReady = true;
            }
            counter = 0;
            bufferWriting = (bufferWriting+1) % 2;
        }
        piUnlock(0);
    }
                                                                                    
    fclose(filePointer);                                                            // Close the file
    printf("Complete reading");
    cleanup(0);
}

void cleanup(int args){
																	                // Set all outputs to LOW
	for(unsigned int i = 0 ; i < sizeof(LEDS) / sizeof(LEDS[0]) ; i++){
		digitalWrite(LEDS[i], LOW);
	}
    digitalWrite(LDAC, LOW);
																	                // Set up each LED to Input (High Impedance)
	for(unsigned int i = 0 ; i < sizeof(LEDS) / sizeof(LEDS[0]) ; i++) {
		pinMode(LEDS[i], INPUT);
	}
    pinMode(LDAC, INPUT);
	printf("Cleaned up.\n");
	exit(0);
}