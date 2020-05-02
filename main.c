#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#define STOP 0

int act = 1;

int main() {
   int *actPtr = &act;
   run(&actPtr);
   actPtr = STOP;
   

   printf("Hello, World!");
   return 0;
}
