#include "linesensor.h"
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

int line_sensor_loop(int *action)
{
    // while
    // {
        if (digitalRead(left) == LOW && digitalRead(middle) == LOW && digitalRead(right) == LOW)
        {
            *action = 0;
        }
        if (digitalRead(LEFT) == HIGH && digitalRead(MID) == LOW && digitalRead(RIGT) == HIGH)
        {
            *action = 1;
        }

        if (digitalRead(left) == HIGH && digitalRead(middle) == HIGH && digitalRead(right) == LOW)
        {
            *action = 3;
        }
        if (digitalRead(left) == LOW && digitalRead(middle) == HIGH && digitalRead(right) == HIGH)
        {
            *action = 2;
        }
    // }

    return -1;
}