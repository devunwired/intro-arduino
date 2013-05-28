/*
 * RgbLed - Library Module to control a 3-color LED
 * Dave Smith
 * Double Encore, Inc.
 */

#include "Arduino.h"
#include "RgbLed.h"

RgbLed::RgbLed(int red, int green, int blue)
{
	pinRed = red;
	pinGreen = green;
	pinBlue = blue;

	digitalWrite(pinRed, 1);
  	digitalWrite(pinGreen, 1);
  	digitalWrite(pinBlue, 1);

  	pinMode(pinRed, OUTPUT);
  	pinMode(pinGreen, OUTPUT);
  	pinMode(pinBlue, OUTPUT);
}

void RgbLed::setRed(int level)
{
	int val = constrain(level, 0, 255);
	analogWrite(pinRed, 255 - val);
}

void RgbLed::setGreen(int level)
{
	int val = constrain(level, 0, 255);
	analogWrite(pinGreen, 255 - val);
}

void RgbLed::setBlue(int level)
{
	int val = constrain(level, 0, 255);
	analogWrite(pinBlue, 255 - val);
}

void RgbLed::setRGB(int red, int green, int blue)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void RgbLed::clear()
{
	setRed(0);
	setGreen(0);
	setBlue(0);
}