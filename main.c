#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#include "linesensor.h"
#define STOP 0

int act = 1;
int *actPtr = &act;

int main() {
   
   // run(actPtr);
   // *actPtr = STOP;
   // left,mid,right
   setup_line_sensors(23,24,25);
   while(1){
      line_sensor_loop(actPtr);
      printf("action: %d\n",*actPtr);
      wait(2);
   }

   printf("Hello, World!");
   return 0;
}
