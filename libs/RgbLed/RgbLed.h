/*
 * RgbLed - Library Module to control a 3-color LED
 * Dave Smith
 * Double Encore, Inc.
 */

#ifndef RgbLed_h
#define RgbLed_h

#include "Arduino.h"

 class RgbLed
 {
 public:
 	RgbLed(int, int, int);
 	void setRed(int);
 	void setGreen(int);
 	void setBlue(int);
 	void setRGB(int, int, int);
 	void clear();

 private:
 	int pinRed;
 	int pinGreen;
 	int pinBlue;
 };

#endif