drive : main.c motors.h motors.c
	gcc -I wall main.c motors.c motors.h -lwiringPi -o drive
rm:
	rm drive
