#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>

#ifndef AVOIDANCE_H
#define AVOIDANCE_H


void init_ir();
void setup();
void loop();
void turn();

#endif 
