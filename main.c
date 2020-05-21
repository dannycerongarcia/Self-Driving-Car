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
#define LEFT 23
#define MID 24
#define RIGT 25
#define OBSTACLESENSOR 1

void checkEchoSensor();
void maneuverObject();
void InitMotors();
void CheckLineSensor(_Bool * isTrail);

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
   //pthread_create(&motor_thread, NULL, motorThreadFunction, (void *)&motor_thread);

   setup_line_sensors(23, 24, 25);
   InitMotors();
   InitDistanceSensor(TRIGGER, ECHO);
   InitSpeedEncoder(SPEEDENCODER);

   while(isTrail) {
       	CheckLineSensor(isTrailPtr);
       	checkEchoSensor();
	sleep(.5);
   }

   pthread_join(motor_thread, NULL);
   printf("Hello, World!");
   return 0;
}



void InitMotors() {
	int m1 = init("motor1", "config2");

    	int m2 = init("motor2", "config1");

    	int m3 = init("motor3", "config1");

    	int m4 = init("motor4", "config2");
}


void checkEchoSensor() {
    if(MeasureDistance() <= 10.0) {
       printf("POTENTIAL OBSTACLE\n");
       stopAll();
       sleep(2);
       if(MeasureDistance() <= 10.0) {
           printf("Obstacle still there\n");
           maneuverObject();
       }
    }
}

void maneuverObject() {
    printf("Turning right\n");
    while(digitalRead(OBSTACLESENSOR) == 1) {
        //pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        right(70);
        //pthread_join(speedEncoderThread, NULL);
    }
    printf("Stopping\n");
    stopAll();
    sleep(2);
    printf("Going forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
         allForward(23);
    }
    printf("Stopping\n");
    stopAll();
    sleep(2);
    printf("Turning left\n");
    //while(digitalRead(OBSTACLESENSOR) == 1) {
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        left(70);
        pthread_join(speedEncoderThread, NULL);
    //}
    printf("Stopping\n");
    stopAll();
    sleep(2);
    printf("Moving forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
        allForward(23);
    }
    printf("Stopping\n");
    stopAll();
    sleep(2);
}

void CheckLineSensor(_Bool *isTrail)
{
    int dlft = digitalRead(LEFT);
    int mid = digitalRead(MID);
    int rght =  digitalRead(RIGT);

    if (dlft == LOW && digitalRead(MID) == LOW && digitalRead(RIGT) == LOW)
    {
        stopAll();
        //*isTrail = FALSE;
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        allForward(23);
    }
    if (dlft == LOW && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        right(23);
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == LOW)
    {
        left(23);
    }
}
