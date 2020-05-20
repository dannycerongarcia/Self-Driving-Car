#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>
#include "DistanceSensor.h"

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
	//printf("Distance to object: %f\n", distance*100/CLOCKS_PER_SEC);
	return distance*100/CLOCKS_PER_SEC;
}



void avoidObstacle(int * action) {
    if(MeasureDistance() <= 10) {
        *action = 0;
        sleep(3);
        if(MeasureDistance() <= 10) {
		maneuverObstacle(action);
	}
    }	    
}


void maneuverObstacle(int * action) {
    while(digitalRead(OBSTACLESENSOR) == 1) {
        *action = 3;
    }
    *action = 0;
    while(digitalRead(OBSTACLESENSOR) == 0) {
        *action = 1;
    }
    *action = 0;
    while(digitalRead(OBSTACLESENSOR) == 1) {
        *action = 2;
    }
    *action = 0;
}

void CheckEchoSensor(struct Motors allMotors []) {
    printf("CHECKECHOSENSOR");
    for(int i = 1; i <= 4; ++i) {
        printf("Motor %d: E: %d, F: %d, R: %d\n", i, digitalRead(allMotors[i].enablePin), digitalRead(allMotors[i].forwardPin), digitalRead(allMotors[i].reversePin));
    }
    if(MeasureDistance() <= 10.0) {
	    printf("POTENTIAL OBSTACLE\n");
	    obstacle = TRUE;
        Stop(Yes, allMotors, &isMoving);
        sleep(2);
        if(MeasureDistance() <= 10.0) {
            printf("Obstacle still there\n");
            maneuverObject(allMotors);
        }
    }
}

void maneuverObject(struct Motors allMotors []) {
    printf("Attempting to go around\n");
    for(int i = 1; i <= 4; ++i) {
        printf("Motor %d: E: %d, F: %d, R: %d\n", i, digitalRead(allMotors[i].enablePin), digitalRead(allMotors[i].forwardPin), digitalRead(allMotors[i].reversePin));
    }
    while(digitalRead(OBSTACLESENSOR) == 1) {
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        Move(allMotors, 'R', 40, &isMoving);
        pthread_join(speedEncoderThread, NULL);
        Stop(Yes, allMotors, &isMoving);
    }
    printf("Going forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
        Move(allMotors, 'F', 23, &isMoving);
    }
    Stop(Yes, allMotors, &isMoving);
    printf("Turning left\n");
    while(digitalRead(OBSTACLESENSOR) == 1) {
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        Move(allMotors, 'L', 40, &isMoving);
        pthread_join(speedEncoderThread, NULL);
        Stop(Yes, allMotors, &isMoving);
    }
    printf("Moving forward\n");
    while(digitalRead(OBSTACLESENSOR) == 0) {
        Move(allMotors, 'F', 23, &isMoving);
    }
    Stop(Yes, allMotors, &isMoving);
}
