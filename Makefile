drive : main.c motors.h motors.c linesensor.c linesensor.h
	gcc -I wall main.c motors.c motors.h linesensor.c linesensor.h -lwiringPi -o drive
rm:
	rm drive
