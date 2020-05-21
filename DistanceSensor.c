#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>
#include "DistanceSensor.h"
#include "motors.h"

#define OBSTACLESENSOR 7
int triggerPin, echoPin;

void InitDistanceSensor(int trigger, int echo) {
	triggerPin = trigger;
	echoPin = echo;

	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
}


double MeasureDistance() {
	clock_t start, end, time;
	double distance;

	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	while(digitalRead(echoPin) == 0) {
		start = clock();
	}
	while(digitalRead(echoPin) == 1) {
		end = clock();
	}
	time = (end - start);
	distance = (time*340)/2.0;
	printf("Distance to object: %f\n", distance*100/CLOCKS_PER_SEC);
	return distance*100/CLOCKS_PER_SEC;
}

void checkEchoSensor() {
    if(MeasureDistance() <= 11.0) {
       printf("POTENTIAL OBSTACLE\n");
       stopAll();
       sleep(2);
       if(MeasureDistance() <= 11.0) {
           printf("Obstacle still there\n");
           maneuverObject();
       }
    }
}

void maneuverObject() {
    printf("Turning right\n");
    printf("%d\n", digitalRead(OBSTACLESENSOR));
    while(digitalRead(OBSTACLESENSOR) == 1) {
        //pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        right(30);
        //pthread_join(speedEncoderThread, NULL);
    }
    printf("Stopping\n");
    stopAll();
    sleep(2);
    printf("Going forward\n");
    printf("%d\n", digitalRead(OBSTACLESENSOR));
    while(digitalRead(OBSTACLESENSOR) == 0) {
         allForward(23);
    }
    printf("Stopping\n");
    stopAll();
    sleep(2);
    printf("Turning left\n");
    //while(digitalRead(OBSTACLESENSOR) == 1) {
        //pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
    left(70);
        //pthread_join(speedEncoderThread, NULL);
    //}
    sleep(3);
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


