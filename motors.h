#ifndef FOO_H_
#define FOO_H_
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
struct config
{
    int e;
    int f;
    int r;
};
// struct for storing the data of the each motor.
// name, modulation pin, and output pins for making the motors run.
struct motor
{
    char motor[6];
    struct config config1;
    struct config config2;
    int e;
    int f;
    int r;
    
    int arrow;
};

int run(int);
int init(char[6],char[7]);
int initHelper(struct motor *, char[7]);
int foward(struct motor *,int,char[7]);
int reverse(struct motor *,int,char[7]);
int stop(struct motor *, char[7]);
int allForward();
int allReverse();
int left();
int right();
int stopAll();


#endif // FOO_H_