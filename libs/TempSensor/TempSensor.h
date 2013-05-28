/*
 * TempSensor - Library Module to monitor a temperature IC
 * Dave Smith
 * Double Encore, Inc.
 */

#ifndef TempSensor_h
#define TempSensor_h

#include "Arduino.h"

class TempSensor
{
public:
	TempSensor(int pin);
	int read();
private:
	int sensorPin;
};

#endif