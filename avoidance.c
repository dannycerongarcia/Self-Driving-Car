
#include <wiringPi.h>
#include <stdio.h>
#include "motors.h"

#define obstacle_pin 7

void init();
void setup();
void loop();
void test();

int obstacle = HIGH; //high means no obstacle
  
void init(){
  if(wiringPiSetup() < 0){
		printf("Initalization failed. ");
		return 1;
    }
	if(wiringPiISR(obstacle_pin, INT_EDGE_FALLING, &test)<0){
		printf("Avoidance Sensor Initalization Failed. \n");
		return 1;
	}
	
	    while(true){
		 setup();
		 loop();
	    }
}

void setup(){
	pinMode(obstacle_pin, INPUT);
}

void loop(){
	obstacle = digitalRead(obstacle_pin);
		if(obstacle == LOW){
			printf("Obstacle Ahead! \n");
			stopAll();
		} 
		else {
			printf("Road Clear.\n");
		}
         delay(300);
}

void test(){
    printf("Obstacle Avoidance test successful\n");
}
