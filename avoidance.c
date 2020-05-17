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

int i = 10;
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
	
	printf("LEFT: %d\n", left_obs);
	printf("RIGHT %d\n", right_obs);
	
	
	if(left_obs == 0 || right_obs == 0){
		allForward(i);
		
		if(left_obs == 0){
		    objLeft = true;
		}  
			if( right_obs ==0 ){
			    objRight = true;
		}  
    
	}
			// if(left_obs == 1 && right_obs ==1){
			// 	delay(100);
			// 	stopAll();
			// }	else {
			// 		stopAll();
			// }
    
            while(left_obs){
            	if(left_obs == 1){
		       stopAll();
		       sleep(3);
		       left(i);
		       printf("Turning LEFT....\n");
			
			//left_obs = false;
		  	  break;
            	}
	    }
        
	   while(right_obs){
            	if(right_obs == 1){
		       stopAll();
			sleep(3);
               		right(i);
			printf("Turning RIGHT....\n");
			
			//right_obs = false;
		    break;
            }
        }
	
}
