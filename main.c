#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#define STOP 0

int *action = STOP;
int main() {
   int 
   run(&action);
   

   printf("Hello, World!");
   return 0;
}
