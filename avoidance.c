#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include "motors.h"
#include "avoidance.h"

// #define IR1 7 //RIGHT
#define IR2 1 //LEFT

void init_ir();
void setup();
void loop();
void test();
void turn();

int i = 30;
bool objLeft = 0;
bool turnLeft = 0;

void init_ir(){
  if(wiringPiSetup() < 0){
		printf("Initalization failed. ");
		return 1;
    }
	setup();

	     while(1){
		 	loop();
	    }	    
}

void setup(){
	// pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
}

void loop(){
	int left_obs = digitalRead(IR2);
	printf(left_obs);

	if(left_obs == 1){
		allForward(i);
	}
	else if(left_obs == 0){
		printf("Left Obstacle Detected: (%d)\n", left_obs);
		turn();

	} else {
		printf("Nothing detected..");
	}
}


void turn(){
	while(digitalRead(IR2) == 0){
		allForward();
	}
		left(i);
}

