#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#define STOP 0

int act = 1;
int *actPtr = &act;

int main() {
   
   run(actPtr);
   *actPtr = STOP;
   init();

   printf("Hello, World!");
   return 0;
}
