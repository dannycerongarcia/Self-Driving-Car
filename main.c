/* 	gcc obstacle.c -lwiringPi
	./a.out 	
*/

#include <wiringPi.h>
#include <stdio.h>

//#define obstacle_pin

void setup();
void loop();
void myISR();

int obstacle_pin = 29;
int obstacle = HIGH; //high means no obstacle


int main(void)
{
	// int LED = 13;
    if(wiringPiSetup() < 0){
		printf("Initalization failed. ");
		return 1;
    }
	if(wiringPiISR(obstacle_pin, INT_EDGE_FALLING, &myISR)<0){
		printf("Initalization ISR failed. \n");
		return 1;
	}
	
    while(1){
         setup();
         loop();
    }
}
       

void setup(){
	//pinMode(LED, OUTPUT);
	pinMode(obstacle_pin, INPUT);
}

void loop(){
	obstacle = digitalRead(obstacle_pin);
		if(obstacle == 0){
			printf("Obstacle!!!\n");
		} 
		else {
			printf("Road Clear!\n");
		}
	delay(500);
}

void myISR(){
    printf("Obstacle Avoidance sensor test\n");
}
