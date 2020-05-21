#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <stdbool.h>
#include "SpeedEncoder.h"

#define PI 3.14

int pin;

void InitSpeedEncoder(int pinNum) {
	pin = pinNum;

	pinMode(pinNum, INPUT);
}

void  SpeedEncoderRotations() {
	printf("THREAD\n");
	int pulses = 0;
	int rotations = 0;
	int dataHigh = 1;
	int data;
	while(rotations != 10) {
	    data = digitalRead(pin);
	    if(data == dataHigh) {
            	while (data != dataHigh) {
                	data = digitalRead(pin);
            	}
            	++pulses;
            	rotations = pulses / 20;
		printf("Rot: %d", rotations);
            }
	}
}
