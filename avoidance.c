  
#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include "motors.h"

 #define IR1 7 //RIGHT
 #define IR2 1 //LEFT

void init_ir();
void setup();
void loop();
void test();

// int left_obs = HIGH;
// int right_obs = HIGH;
int i = 15;
int counter = 5;
bool objLeft = false;
bool objRight = false;

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
	pinMode(IR2, INPUT);
	pinMode(IR1, INPUT);
}

void loop(){
	int right_obs = digitalRead(IR1);
	int left_obs = digitalRead(IR2);
	
	printf("left_obs %d\n", left_obs);
	printf("right_obs %d\n", right_obs);
	
	
	if(left_obs == 0 || right_obs == 0){
		printf("obstacle to the left\n");
		allForward(i);
		objLeft = true;
			if(left_obs == 1 && right_obs ==1){
				objLeft = false;
				delay(100);
				stopAll();
			}	else {
					stopAll();
			}
	}
	         delay(500);
}

