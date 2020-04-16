#include <motors.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
int init(char[6],char[7]);
int initHelper(struct motor *, char[7]);
int foward(struct motor *,int,char[7]);
int reverse(struct motor *,int,char[7]);
int stop(struct motor *, char[7]);
int run(int);