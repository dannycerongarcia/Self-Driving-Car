#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#define STOP 0

int act = STOP;

int main() {
   int *actPtr = &act;
   run(&actPtr);
   

   printf("Hello, World!");
   return 0;
}
