#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "motors.h"
#include "linesensor.h"
#include "DistanceSensor.h"

#define TRIGGER 21
#define ECHO 22

int act = 0;
int *actPtr = &act;
pthread_t motor_thread;
_Bool isTrail = TRUE;
_Bool * isTrailPtr = &isTrail;
//---------------------------------cleaning up threads--------------------------------
void handler(int sig)
{
   printf("Execption ctrl-c Caught %d", sig);
   stopAll();
   exit(0);
}
//------------------------------------------------------------------------------------
void *motorThreadFunction(void *vargp)
{
   // pthread_cleanup_push(handler, NULL);
   run(actPtr);
}


int main()
{
   wiringPiSetup();
   //    threadinf the motors function
   signal(SIGINT,handler);
   pthread_create(&motor_thread, NULL, motorThreadFunction, (void *)&motor_thread);

   setup_line_sensors(23, 24, 25);
   InitDistanceSensor(TRIGGER, ECHO);

   while(isTrail) {
       checkLineSensor(actPtr, isTrailPtr);
       avoidObstacle(actPtr);
   }

   pthread_join(motor_thread, NULL);
   printf("Hello, World!");
   return 0;
}
