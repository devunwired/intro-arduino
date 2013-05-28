/*
 * TempSensor - Library Module to monitor a temperature IC
 * Dave Smith
 * Double Encore, Inc.
 */

#include "Arduino.h"
#include "TempSensor.h"

TempSensor::TempSensor(int pin)
{
	sensorPin = pin;
}

int TempSensor::read()
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
   	* The change in voltage is scaled to a temperature coefficient of 10.0
   	* mV/degC (typical) for the MCP9700/9700A and 19.5 mV/degC (typical)
   	* for the MCP9701/9701A. The out- put voltage at 0 degC is also scaled
   	* to 500 mV (typical) and 400 mV (typical) for the MCP9700/9700A and
   	* MCP9701/9701A, respectively. VOUT = TC•TA+V0degC
   	*/
  	double kVoltageAtZeroCmv = 400;
  	double kTemperatureCoefficientmvperC = 19.5;
  	double ambientTemperatureC = ((double) voltagemv - kVoltageAtZeroCmv)
		/ kTemperatureCoefficientmvperC;
  	double temperatureF = (9.0 / 5.0) * ambientTemperatureC + 32.0;

  	return temperatureF;
}