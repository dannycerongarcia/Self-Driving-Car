
#include <wiringPi.h>
#include <stdio.h>
#include "motors.h"

#define IR1 7
#define IR2 12

void init();
void setup();
void loop();
void test();

int left_obs = HIGH; //high means no obstacle
int right_obs = HIGH;
int i = 10;
  
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
	pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
}

void loop(){
	left_obs = digitalRead(IR1);
	right_obs = digitalRead(IR2);
		if(left_obs == 0){
			printf("Obstacle to the left \n");
			right(i);
			delay(100);
			allforward(i);
			//stopAll();
		} 
		if(right_obs == 0){
			printf("Obstacle to the right \n");
			left(i);
			delay(100);
			allforward(i);
			//stopAll();
		} 
		else {
			printf("Road Clear.\n");
		}
         delay(300);
}

void test(){
    printf("Obstacle Avoidance test successful\n");
}
