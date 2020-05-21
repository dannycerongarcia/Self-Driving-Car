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

