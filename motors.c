/**************************************************************             
* sources: 
*          https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c
*          https://github.com/sbcshop/MotorShield/blob/master/PiMotor.py
**************************************************************/
// resources:
//
#include "motors.h"
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3
#define REVERSE 4

// #include <dos.h>
// struct for each motor configurations

//  arrowpins={1:33,2:35,3:37,4:36}

// motor variable initialization
// pins 11,15,13,11,13,15,4
struct motor motor1 = {"motor1", 0, 3, 2, 0, 2, 3, 0};
struct motor *motor1Ptr = &motor1;

struct motor motor2 = {"motor2", 6, 4, 5, 6, 5, 4, 0};
struct motor *motor2Ptr = &motor2;

struct motor motor3 = {"motor3", 12, 13, 14, 12, 14, 13, 0};
struct motor *motor3Ptr = &motor3;

struct motor motor4 = {"motor4", 26, 10, 11, 26, 11, 10, 0};
struct motor *motor4Ptr = &motor4;

// params motor name, motor configuration
// it calls the initHelper function to set up the pins for the motor being initialized
int init(char motor[6], char config[7])
{
    int check = -1;
    if (motor == NULL || config == NULL || (strcmp(motor, "") == 0) || (strcmp(config, "") == 0))
    {
        printf("invalid input, ");
        printf("%s motor: ", motor);
        printf("%s config: ", config);
    }
    else if (strcmp(motor, "motor1") == 0)
    {
        check = initHelper(&motor1, config);
    }
    else if (strcmp(motor, "motor2") == 0)
    {
        check = initHelper(&motor2, config);
    }
    else if (strcmp(motor, "motor3") == 0)
    {
        check = initHelper(&motor3, config);
    }
    else if (strcmp(motor, "motor4") == 0)
    {
        check = initHelper(&motor4, config);
    }
    return check;
}
// params: pointer to the motor being initialized, configuration of the motor
// it configures the pins the motor will use.
int initHelper(struct motor *mot, char config[7])
{
    // configuration 1
    // using pointer type 1
    if (strcmp(config, "config1") == 0)
    {
        (*mot).e = (*mot).config1.e;
        (*mot).f = (*mot).config1.f;
        (*mot).r = (*mot).config1.r;

        // set the pins
        pinMode((*mot).config1.e, OUTPUT);
        pinMode((*mot).config1.f, OUTPUT);
        pinMode((*mot).config1.r, OUTPUT);
        softPwmCreate((*mot).config1.e, 0, 100); //set PWM channal with range
        softPwmWrite((*mot).config1.e, 0);

        // PinMode((*mot).config1.e,PWM_OUTPUT);
        // pwmWrite((*mot).config.e,0)
        softPwmWrite((*mot).config1.e, 0);
        digitalWrite((*mot).config1.f, LOW);
        digitalWrite((*mot).config1.r, LOW);
        return 0;
    }
    // configuration 2
    // using pointer type 2
    if (strcmp(config, "config2") == 0)
    {
        mot->e = (*mot).config2.e;
        mot->f = (*mot).config2.f;
        mot->r = (*mot).config2.r;
        // set the pins

        // setting pins
        pinMode(mot->config2.e, OUTPUT);
        pinMode(mot->config2.f, OUTPUT);
        pinMode(mot->config2.r, OUTPUT);
        softPwmCreate(mot->config1.e, 0, 100); //set PWM channal with range

        // PinMode(mot->config1.e,PWM_OUTPUT);
        // pwmWrite(mot->config.e,0)
        softPwmWrite(mot->config2.e, 0);
        digitalWrite(mot->config2.f, LOW);
        digitalWrite(mot->config2.r, LOW);
        return 0;
    }
    else
    {
        printf("invalid config");
    }
    return -1;
}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to high voltage and the pin module to the speed value.
int foward(struct motor *mot, int speed, char config[7])
{
    // pwmWrite(mot->config.e,speed)
    softPwmWrite(mot->e, speed);
    digitalWrite(mot->f, HIGH);
    digitalWrite(mot->r, LOW);
    return 0;
}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to high voltage and the pin module to the speed value.
int reverse(struct motor *mot, int speed, char config[7])
{

    softPwmWrite(mot->e, speed);
    digitalWrite(mot->f, LOW);
    digitalWrite(mot->r, HIGH);
    return 0;
}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to 0 voltage and the pin module to 0.
int stop(struct motor *mot, char config[7])
{
    // pwmWrite(mot->config.e,speed)
    softPwmWrite(mot->e, 0);
    digitalWrite(mot->f, LOW);
    digitalWrite(mot->r, LOW);
    return 0;
}
int allForward(int i)
{
    foward(&motor1, 26, "config2");
    foward(&motor2, 30, "config1");
    foward(&motor3, 26, "config1");
    foward(&motor4, 26, "config2");
    delay(80);
    foward(&motor1, i, "config2");
    foward(&motor2, i, "config1");
    foward(&motor3, i, "config1");
    foward(&motor4, i, "config2");
    return 0;
}
int allReverse(int i)
{
    reverse(&motor1, 26, "config1");
    reverse(&motor2, 20, "config2");
    reverse(&motor3, 26, "config1");
    reverse(&motor4, 26, "config2");
    delay(80);
    reverse(&motor1, i, "config1");
    reverse(&motor2, i, "config2");
    reverse(&motor3, i, "config1");
    reverse(&motor4, i, "config2");
    return 0;
}
int left(int i)
{
    reverse(&motor1, 60, "config1");
    foward(&motor2, 60, "config2");
    reverse(&motor3, 60, "config1");
    foward(&motor4, 60, "config2");
    delay(80);
    reverse(&motor1, i, "config1");
    foward(&motor2, i, "config2");
    reverse(&motor3, i, "config1");
    foward(&motor4, i, "config2");
    return 0;
}
int right(int i)
{
    foward(&motor1, 60, "config1");
    reverse(&motor2, 60, "config2");
    foward(&motor3, 60, "config1");
    reverse(&motor4, 60, "config2");
    delay(80);
    foward(&motor1, i, "config1");
    reverse(&motor2, i, "config2");
    foward(&motor3, i, "config1");
    reverse(&motor4, i, "config2");
    return 0;
}
int stopAll()
{
    stop(&motor1, "config1");
    stop(&motor2, "config2");
    stop(&motor3, "config1");
    stop(&motor4, "config2");
}

/*
param: pointer to the action in main
*/
int run(int *action)
{
    int m1 = init("motor1", "config2");
    int m2 = init("motor2", "config1");
    int m3 = init("motor3", "config1");
    int m4 = init("motor4", "config2");

    // speed
    int i = 10;
   
    int prev  =0;
    while (*action != -1)
    {
        if (*action == FORWARD && prev != FORWARD)
        {
            allForward(i);
        }
        if (*action == REVERSE && prev !=  REVERSE)
        {
            allReverse(i);
        }
        if (*action == LEFT && prev != LEFT)
        {
            //turn left
            left(i);
        }
        if (*action == RIGHT && prev != RIGHT)
        {
            //turn right
            right(i);
        }
        if (*action == STOP && prev != STOP)
        {
            stopAll();
        }
        prev = *action;
    }
    return 0;
}
