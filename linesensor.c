#include "linesensor.h"
int left = 0;
int middle = 0;
int right = 0;

void setup_line_sensors(int lft, int mid, int rght)
{
    if (wiringPiSetup() < 0)
    {
        printf("wiringPiSetUp failed");
    }
    pinMode(lft, INPUT);
    pinMode(mid, INPUT);
    pinMode(rght, INPUT);
    left = lft;
    middle = mid;
    right = rght;
}

int line_sensor_loop(int *action)
{
    // while
    // {
        if (digitalRead(left) == LOW && digitalRead(middle) == LOW && digitalRead(right) == LOW)
        {
            *action = 0
        }
        if (digitalRead(left) == HIGH && digitalRead(middle) == LOW && digitalRead(right) == HIGH)
        {
            *action = 1
        }

        if (digitalRead(left) == HIGH && digitalRead(middle) == HIGH && digitalRead(right) == LOW)
        {
            *action = 3
        }
        if (digitalRead(left) == LOW && digitalRead(middle) == HIGH && digitalRead(right) == HIGH)
        {
            *action = 2
        }
    // }

    return -1;
}