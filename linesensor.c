#include <unistd.h>
#include "linesensor.h"
#include "motors.h"

int LEFT = 0;
int MID = 0;
int RIGHT = 0;
int FAR_RIGHT = 0;
int FAR_LEFT = 0;

void setup_line_sensors(int lft, int mid, int rght, int farRight, int farLeft)
{
    if (wiringPiSetup() < 0)
    {
        printf("wiringPiSetUp failed");
    }
    pinMode(lft, INPUT);
    pinMode(mid, INPUT);
    pinMode(rght, INPUT);
    pinMode(farRight, INPUT);
    pinMode(farLeft, INPUT);
    LEFT = lft;
    MID = mid;
    RIGHT = rght;
    FAR_RIGHT = farRight;
    FAR_LEFT = farLeft;
}

void checkLineSensor(_Bool *isTrail)
{
    int dlft = digitalRead(LEFT);
    int mid = digitalRead(MID);
    int right =  digitalRead(RIGHT);

    if (dlft == LOW && digitalRead(MID) == LOW && right  == LOW)
    {
        stopAll();
        sleep(1);
        left(50);
        sleep(.5);
        if(dlft == LOW && mid == LOW && rght == LOW) {
            right(50);
            sleep(1);
            if(dlft == LOW && mid == LOW && rght == LOW) {
                stopAll();
            }
        }
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        allForward(20);
    }
    if (dlft == LOW && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        right(25);
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == LOW)
    {
        left(25);
    }
    if(digitalRead(FAR_RIGHT) == HIGH) {
        right(25);
    }
    if(digitalRead(FAR_LEFT) == HIGH) {
        left(25);
    }
}
