#include <unistd.h>
#include "linesensor.h"
#include "motors.h"

int LEFT = 0;
int MID = 0;
int RIGT = 0;

void setup_line_sensors(int lft, int mid, int rght)
{
    if (wiringPiSetup() < 0)
    {
        printf("wiringPiSetUp failed");
    }
    pinMode(lft, INPUT);
    pinMode(mid, INPUT);
    pinMode(rght, INPUT);
    LEFT = lft;
    MID = mid;
    RIGT = rght;
}

void checkLineSensor(_Bool *isTrail)
{
    int dlft = digitalRead(LEFT);
    int mid = digitalRead(MID);
    int rght =  digitalRead(RIGT);

    if (dlft == LOW && digitalRead(MID) == LOW && digitalRead(RIGT) == LOW)
    {
        stopAll();
        left(25);
        sleep(1);
        if(dlft == LOW && mid == LOW && rght == LOW) {
            right(25);
            sleep(2);
            if(dlft == LOW && mid == LOW && rght == LOW) {
                *isTrail = FALSE;
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
}
