#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "motors.h"
#include "linesensor.h"
#define STOP 0

int act = ;
int *actPtr = &act;

void *motorThreadFunction(void *vargp){run(actPtr);}

int main() {
   

   // threadinf the motors function
   pthrread_t thread_id;
   pthread_create(&thread_id,NULL,motorThreadFunction,NULL);
   pthread_join(thread_id,NULL)
   printf("motor in thread: %d\n",thread_id);
   
   // *actPtr = STOP;
   // left,mid,right

   //  run(actPtr);
    *actPtr = STOP;
   // left,mid,right;

   setup_line_sensors(23,24,25);
   while(1){
      line_sensor_loop(actPtr);
      printf("action: %d\n",*actPtr);
      sleep(2);
   }

   printf("Hello, World!");
   return 0;
}
