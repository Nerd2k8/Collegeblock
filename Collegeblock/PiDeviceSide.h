#ifndef PIDEVICESIDE_H
#define PIDEVICESIDE_H


#include <wiringPi.h>


enum Pin
{
	Pin17 = 0,
	Pin27 = 2,
	Pin22 = 3,
	Pin05 = 21,
	Pin06 = 22,
	Pin13 = 23,
	Pin19 = 24,
	Pin26 = 25,
	Pin18 = 1,
	Pin23 = 4,
	Pin24 = 5,
	Pin25 = 6,
	Pin12 = 26,
	Pin16 = 27,
	Pin20 = 28,
	Pin21 = 29
}; 

bool initGPIOs();

void activatePin(int pin);

void deactivatePin(int pin);

void changePinStat(int pin);


#endif
