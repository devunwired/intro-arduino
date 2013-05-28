/*
 * LightSensor - Library Module to monitor a light sensor IC
 * Dave Smith
 * Double Encore, Inc.
 */

#ifndef LightSensor_h
#define LightSensor_h

#include "Arduino.h"

class LightSensor
{
public:
	LightSensor(int pin);
	int read();
	bool isDark();
	bool isBright();
private:
	int sensorPin;
};

#endif