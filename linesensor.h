#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

void setup_line_sensors(int, int, int);

void checkLineSensor(int *, _Bool *);