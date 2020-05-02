#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
int main() {
   run(1);
   delay(3000); 

   printf("Hello, World!");
   return 0;
}
