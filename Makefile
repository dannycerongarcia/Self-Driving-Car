robotCar: main.c motors.c linesensor.c DistanceSensor.c SpeedEncoder.c
	gcc -o robotCar main.c motors.c linesensor.c DistanceSensor.c SpeedEncoder.c -I. -lwiringPi -lpthread
