#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <zconf.h>
#include <time.h>

//motor 1 left front and 2 are right front
// motor 3 left back, motor 4 right back

#define motor1_enable 0
#define motor1_control_f 2
#define motor1_control_r 3

#define motor2_enable 6
#define motor2_control_f 4
#define motor2_control_r 5

#define motor3_enable 12
#define motor3_control_f 13
#define motor3_control_r 14

#define motor4_enable 26
#define motor4_control_f 11
#define motor4_control_r 10

#define speed_sensor = 29
//number of pulses per revolution (ppr)
#define ppr 20
int state = 0;
int prev_state = 0;
int rotations = 0;
// number of steps to full rotation
int steps_to_ppr = 0;
// total number of pulses counted in a given interval
int total_steps = 0;


struct motor motor1 = {motor1_enable, motor1_control_f, motor1_control_r};
struct motor motor2 = {motor2_enable, motor2_control_f, motor2_control_r};
struct motor motor3 = {motor3_enable, motor3_control_f, motor3_control_r};
struct motor motor4 = {motor4_enable, motor4_control_f, motor4_control_r};



void setup();
void forward(struct motor *, int);
void reverse(struct motor *, int);
void stop(struct motor *);
void right(struct motor *, struct motor *);
void left(struct motor *, struct motor *);



int main(void) {
  setup();

  forward(&motor1);
  forward(&motor2);
  forward(&motor3);
  forward(&motor4);

  forward(&motor1);
  reverse(&motor2);
  forward(&motor3);
  reverse(&motor4);

while(rotations < 5) {
  loop();
}

  rotations = 0;

  stop(&motor1);
  stop(&motor2);
  stop(&motor3);
  stop(&motor4);

  delay(3000);

  forward(&motor1);
  forward(&motor2);
  forward(&motor3);
  forward(&motor4);

  delay(3000);

  stop(&motor1);
  stop(&motor2);
  stop(&motor3);
  stop(&motor4);

  forward(&motor1);
  reverse(&motor2);
  forward(&motor3);
  reverse(&motor4);

  while(rotations < 5) {
    loop();
  }



  stop(&motor1);
  stop(&motor2);
  stop(&motor3);
  stop(&motor4);




}

void loop() {
  state = digitalRead(speed_sensor);
  if(state != prev_state) {
    steps_to_ppr++;
    total_steps++;
  }

  prev_state = state;

  if(steps_to_ppr == ppr) {
    rotations++;

    steps_to_ppr = 0;
    printf("Number of Rotations: %d\n", rotations);

  }



void setup() {
    if (wiringPiSetup() == -1) {
        printf("Setup failed\n");
        exit(1);
    }

    pinMode(motor1.enable, OUTPUT);
    pinMode(motor1.forward, OUTPUT);
    pinMode(motor1.reverse, OUTPUT);
    softPwmCreate(motor1.enable, 0, 100);

    pinMode(motor2.enable, OUTPUT);
    pinMode(motor2.forward, OUTPUT);
    pinMode(motor2.reverse, OUTPUT);
    softPwmCreate(motor2.enable, 0, 100);

    pinMode(motor3.enable, OUTPUT);
    pinMode(motor3.forward, OUTPUT);
    pinMode(motor3.reverse, OUTPUT);
    softPwmCreate(motor3.enable, 0, 100);

    pinMode(motor4.enable, OUTPUT);
    pinMode(motor4.forward, OUTPUT);
    pinMode(motor4.reverse, OUTPUT);
    softPwmCreate(motor4.enable, 0, 100);

    pinMode(speed_sensor, INPUT);


}

void forward(struct motor * selectedMotor, int speed) {
    softPwmWrite(selectedMotor->enable, speed);
    digitalWrite(selectedMotor->forward, HIGH);
    digitalWrite(selectedMotor->reverse, LOW);
}

void reverse(struct motor * selectedMotor, int reverse_speed) {
    softPwmWrite(selectedMotor->enable, reverse_speed);
    digitalWrite(selectedMotor->forward, LOW);
    digitalWrite(selectedMotor->reverse, HIGH);
}

void stop(struct motor * selectedMotor) {
    softPwmWrite(selectedMotor->enable, 0);
    digitalWrite(selectedMotor->forward, LOW);
    digitalWrite(selectedMotor->reverse, LOW);
}

// motor 1, 3 = left
// motor 2, 4 = right
void right(struct motor * leftMotor, struct motor * rightMotor) {
    reverse(rightMotor, reverse_sd);
    forward(leftMotor, turn_speed);
}

void left(struct motor * leftMotor, struct motor * rightMotor) {
    reverse(leftMotor, reverse_sd);
    forward(rightMotor, turn_speed);
}
