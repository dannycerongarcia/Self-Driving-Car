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
#include "avoidance.h"

#define TRIGGER 21
#define ECHO 22
#define SPEEDENCODER 28

void initMotors();
void initSensors();

int act = 0;
int *actPtr = &act;
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




int main() {
   	wiringPiSetup();
   	//    threadinf the motors function
   	signal(SIGINT,handler);
	
   	initMotors();
	initSensors();

   	while(isTrail) {
       		checkLineSensor(isTrailPtr);
       		checkEchoSensor();
		sleep(.5);
   	}

	return 0;
}



void initMotors() {
	int m1 = init("motor1", "config2");
    	int m2 = init("motor2", "config1");
    	int m3 = init("motor3", "config1");
    	int m4 = init("motor4", "config2");
}

void initSensors() {
	setup_line_sensors(23, 24, 25, 27, 29);
   	InitDistanceSensor(TRIGGER, ECHO);
   	InitSpeedEncoder(SPEEDENCODER);
}

