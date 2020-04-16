/*****************************************************************
* Class: CSC 615-01 Spring 2020
* Name: Onubulachi Wami
* Student ID: 918781050
* Project: Assignment 3 - Motor Control
*
* File: motor.c
*
* Description: This program is a demo of the motor to ensure that we
* properly know how to make the motor move forward, in reverse, and
* stop as well as control the speed. (Demonstrated by halving the Speed
* of reversing.
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <zconf.h>

#define motor1_enable 0
#define motor1_control_f 2
#define motor1_control_r 3

#define motor2_enable 6
#define motor2_control_f 4
#define motor2_control_r 5

#define speed_sensor 21
//number of pulses per revolution (ppr)
#define ppr 18
int state = 0;
int prev_state = 0;
int rotations = 0;
int steps_to_ppr = 0;

int speed = 50;


struct motor {
    int enable;
    int forward;
    int reverse;
};

struct motor motor1 = {motor1_enable, motor1_control_f, motor1_control_r};
struct motor motor2 = {motor2_enable, motor2_control_f, motor2_control_r};

void setup();
void forward(struct motor *);
void reverse(struct motor *);
void stop(struct motor *);
void right(struct motor *, struct motor *);
void left(struct motor *, struct motor *);
void loop();

void setup() {
    if (wiringPiSetup() == -1) {
        printf("Setup failed\n");
        exit(1);
    }

    pinMode(motor1.enable, OUTPUT);
    pinMode(motor1.forward, OUTPUT);
    pinMode(motor1.reverse, OUTPUT);
    softPwmCreate(motor1.enable, 0, 100);

    //pinMode(motor2.enable, OUTPUT);
    //pinMode(motor2.forward, OUTPUT);
    //pinMode(motor2.reverse, OUTPUT);
    //softPwmCreate(motor2.enable, 0, 100);

    pinMode(speed_sensor, INPUT);
    digitalWrite(speed_sensor, HIGH);

}

void forward(struct motor * selectedMotor) {
    softPwmWrite(selectedMotor->enable, speed);
    digitalWrite(selectedMotor->forward, HIGH);
    digitalWrite(selectedMotor->reverse, LOW);
}

void reverse(struct motor * selectedMotor) {
    softPwmWrite(selectedMotor->enable, speed);
    digitalWrite(selectedMotor->forward, LOW);
    digitalWrite(selectedMotor->reverse, HIGH);
}

//
void stop(struct motor * selectedMotor) {
    softPwmWrite(selectedMotor->enable, 0);
    digitalWrite(selectedMotor->forward, LOW);
    digitalWrite(selectedMotor->reverse, LOW);
}

// accelerate without changing the direction of the motor
void accelerate(struct motor * leftMotor, struct motor * rightMotor) {
  speed+=10;
  softPwmWrite(leftMotor->enable, speed);
  softPwmWrite(rightMotor->enable, speed);
}

// slow down the motor without changing direction of the motor
void decelerate(struct motor * leftMotor, struct motor * rightMotor) {
  speed-=10;
  softPwmWrite(leftMotor->enable, speed);
  softPwmWrite(rightMotor->enable, speed);
}

// motor 1 = left
// motor 2 = right
void right(struct motor * leftMotor, struct motor * rightMotor) {
    reverse(&rightMotor);
    forward(&leftMotor);
}

void left(struct motor * leftMotor, struct motor * rightMotor) {
    reverse(&leftMotor);
    forward(&rightMotor);
}

void loop() {
  state = digitalRead(speed_sensor);
  if(state != prev_state)
    steps_to_ppr++;

  prev_state = state;

  if(steps_to_ppr == ppr) {
    rotations++;
    steps_to_ppr = 0;
    printf("Number of Rotations: %d", rotations);
  }

}

int main() {
  setup();
  forward(&motor1);
  while(rotations < 50) {
    loop();
  }
  stop(&motor1);
  sleep(1);
  printf("Ending Program");
}
