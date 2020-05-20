robotCar: main.c motors.c linesensor.c DistanceSensor.c
	gcc -o robotCar main.c motors.c linesensor.c DistanceSensor.c -I. -lwiringPi -lpthread
