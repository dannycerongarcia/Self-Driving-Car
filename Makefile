drive : main.c motors.h
	gcc -I wall main.c -lwiringPi -o drive
rm:
	rm drive