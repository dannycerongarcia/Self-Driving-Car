#include <wiringPi.h>
#include <stdio.h>
#include "motors.h"

#define IR1 7
#define IR2 1

void init();
void setup();
void loop();
void test();

int left_obs = HIGH; //high means no obstacle
int right_obs = HIGH;
int i = 10;
int counter = 0;
  
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
	
		while(left_obs == 0){
			printf("Obstacle to the left \n");
			counter+=1;
			printf("counter: %d\n", counter);
		}
			//obstacle not to the left anymore
			if(left_obs == 1){ 
				printf("ready to turn... \n");
				delay(300);
				left(counter); 
				allforward(i);
			}

		
		while(right_obs == 0){
			printf("Obstacle to the left \n");
			counter+=1;
			printf("counter: %d\n", counter);
		}
			//obstacle not to the left anymore
			if(right_obs == 1){ 
				printf("ready to turn... \n");
				delay(300);
				right(counter); 
				allforward(i);
			}
			else {
				printf("Road Clear.\n");
			}
	         delay(300);
}

void test(){
    printf("Obstacle Avoidance test successful\n");
}
