#include "PiDeviceSide.h"
#include "MainWindow.h"




bool initGPIOs()
{
	if (wiringPiSetup() == -1)
	{
		printf(" wiringPi setup failed! ");
		exit(-1);
	}
	
	pinMode(Pin17, OUTPUT);
	digitalWrite(Pin17, HIGH);
	pinMode(Pin27, OUTPUT);
	digitalWrite(Pin27, HIGH);
	pinMode(Pin22, OUTPUT);
	digitalWrite(Pin22, HIGH);
	pinMode(Pin05, OUTPUT);
	digitalWrite(Pin05, HIGH);
	pinMode(Pin06, OUTPUT);
	digitalWrite(Pin06, HIGH);
	pinMode(Pin13, OUTPUT);
	digitalWrite(Pin13, HIGH);
	pinMode(Pin19, OUTPUT);
	digitalWrite(Pin19, HIGH);
	pinMode(Pin26, OUTPUT);
	digitalWrite(Pin26, HIGH);
	
	pinMode(Pin18, OUTPUT);
	digitalWrite(Pin18, HIGH);
	pinMode(Pin23, OUTPUT);
	digitalWrite(Pin23, HIGH);
	pinMode(Pin24, OUTPUT);
	digitalWrite(Pin24, HIGH);
	pinMode(Pin25, OUTPUT);
	digitalWrite(Pin25, HIGH);
	pinMode(Pin12, OUTPUT);
	digitalWrite(Pin12, HIGH);
	pinMode(Pin16, OUTPUT);
	digitalWrite(Pin16, HIGH);
	pinMode(Pin20, OUTPUT);
	digitalWrite(Pin20, HIGH);
	pinMode(Pin21, OUTPUT);
	digitalWrite(Pin21, HIGH);
	
	return true;
}

void deactivatePin(int pin)
{
	if (digitalRead(pin) == LOW)
		digitalWrite(pin, HIGH);
}

void activatePin(int pin)
{
	if (digitalRead(pin) == HIGH)
		digitalWrite(pin, LOW);
}

void changePinStat(int pin)
{
	if (digitalRead(pin))
	{
		digitalWrite(pin, LOW);
	}
	else 
	{
		digitalWrite(pin, HIGH);
	}
}

