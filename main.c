#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#include "DistanceSensor.h"
#define STOP 0
#define DISTANCESENSORTRIGGER 21
#define DISTANCESENSORECHO 22

int act = 1;
int *actPtr = &act;

int main() {
   wiringPiSetup();
   InitDistanceSensor(DISTANCESENSORTRIGGER, DISTANCESENSORECHO);   
   
   while(1) {
      run(actPtr);
      avoidObstacle(actPtr);  
   }
   *actPtr = STOP;
   

   printf("Hello, World!");
   return 0;
}
