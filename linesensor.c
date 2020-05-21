#include "linesensor.h"
int LEFT = 0;
int MID = 0;
int RIGT = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
    *action = 0;

    int dlft = digitalRead(LEFT);
    int mid = digitalRead(MID);
    int rght =  digitalRead(RIGT);

    if (dlft == LOW && digitalRead(MID) == LOW && digitalRead(RIGT) == LOW)
    {
        stopAll();
        //*isTrail = FALSE;
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        allForward(20);
    }
    if (dlft == LOW && digitalRead(MID) == HIGH && digitalRead(RIGT) == HIGH)
    {
        right(30);
    }
    if (dlft == HIGH && digitalRead(MID) == HIGH && digitalRead(RIGT) == LOW)
    {
        left(3);
    }
}
