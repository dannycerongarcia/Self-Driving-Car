#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "motors.h"
#include "linesensor.h"

int act = 0;
int *actPtr = &act;
pthread_t motor_thread;
//---------------------------------cleaning up threads--------------------------------
void handler(int sig)
{
   printf("Execption ctrl-c Caught %d", sig);
   exit(0);
}
//------------------------------------------------------------------------------------
void *motorThreadFunction(void *vargp)
{
   // pthread_cleanup_push(handler, NULL);
   run(actPtr);
}


int main()
{

   //    threadinf the motors function
   signal(SIGINT,handler);
   pthread_create(&motor_thread, NULL, motorThreadFunction, (void *)&motor_thread);

   setup_line_sensors(23, 24, 25);

   line_sensor_loop(actPtr);

   pthread_join(motor_thread, NULL);
   printf("Hello, World!");
   return 0;
}
