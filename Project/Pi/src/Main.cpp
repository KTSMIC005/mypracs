#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "wiringPi.h"
#include "wiringSerial.h"

int main ()
{
  int fd ;

  if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  delay(3);

  serialPutchar(fd, 9);
  //serialPutchar(fd, 10);

  while (serialDataAvail (fd)){
      printf (" -> %3d", serialGetchar (fd)) ;
  }  

  return 0 ;
}