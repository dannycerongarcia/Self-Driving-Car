#include <stdio.h>

#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H


void InitDistanceSensor(int, int);

double MeasureDistance();

void checkEchoSensor();

void maneuverObject();

#endif //DISTANCESENSOR_H
