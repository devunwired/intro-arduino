/*
 * RgbLed - Library Module to monitor a light sensor IC
 * Dave Smith
 * Double Encore, Inc.
 */

#include "Arduino.h"
#include "LightSensor.h"

LightSensor::LightSensor(int pin)
{
	sensorPin = pin;
}

int LightSensor::read()
{
	int val = analogRead(sensorPin);
  	/*
   	 * Arduino board contains a 10-bit analog to digital converter. This
   	 * will map input voltages between 0 and 5 volts into integer values
   	 * between 0 and 1023. This yields a resolution between readings of: 5
   	 * volts / 1024 units or, .0049 volts (4.9 mV) per unit.
   	 */
  	double voltagemv = val * 4.9;
  
	/*
	 * The TPS852 light sensor outputs a constant current that is linearly
	 * proportional to the luminance value (in lux) of the ambient light. The
	 * output is 0.35uA / lux (typical).  The demo shield passes this current
	 * through a 51K resistor. VOUT = Iout * 51K, so the light coefficient
	 * is 17.85 mV/lux.
	 */
  	double kLightCoefficientLux = 17.85;
  	double light = voltagemv / kLightCoefficientLux;
  
  	return light;
}

bool LightSensor::isDark()
{
	int val = read();
	return (val < 100);
}

bool LightSensor::isBright()
{
	int val = read();
	return (val > 150);
}