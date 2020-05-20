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
#include "SpeedEncoder.h"

#define TRIGGER 21
#define ECHO 22
#define SPEEDENCODER 29

void checkEchoSensor();
void maneuverObject();

int act = 0;
int *actPtr = &act;
pthread_t motor_thread, speedEncoderThread;
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
   InitSpeedEncoder(SPEEDENCODER);

   while(isTrail) {
       checkLineSensor(actPtr, isTrailPtr);
       checkEchoSensor();
   }

   pthread_join(motor_thread, NULL);
   printf("Hello, World!");
   return 0;
}


void checkEchoSensor() {
    printf("CHECKECHOSENSOR");
    if(MeasureDistance() <= 10.0) {
	    printf("POTENTIAL OBSTACLE\n");
	    obstacle = TRUE;
       stopAll();
       sleep(2);
       if(MeasureDistance() <= 10.0) {
           printf("Obstacle still there\n");
           maneuverObject();
       }
    }
}

void maneuverObject() {
    printf("Attempting to go around\n");
    while(digitalRead(OBSTACLESENSOR) == 1) {
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        right(40);
        pthread_join(speedEncoderThread, NULL);
        stopAll();
    }
    printf("Going forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
         allForward(23);
    }
    stopAll();
    printf("Turning left\n");
    while(digitalRead(OBSTACLESENSOR) == 1) {
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        left(40);
        pthread_join(speedEncoderThread, NULL);
        stopAll();
    }
    printf("Moving forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
        allForward(23);
    }
    stopAll();
}

