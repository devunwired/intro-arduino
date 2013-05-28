#include <RgbLed.h>

//Set digital pins appropriately for your board
#define PIN_RED    2
#define PIN_GREEN  4
#define PIN_BLUE   3

//Create an LED instance
RgbLed Led(PIN_RED, PIN_GREEN, PIN_BLUE);

void setup() {
  //Initialize the LED to off
  Led.clear();
}

void loop() {
  //All channel on (white color)
  Led.setRGB(255, 255, 255);
  delay(500);
  //Remove red channel
  Led.setRed(0);
  delay(500);
  //Remove blue channel
  Led.setBlue(0);
  delay(500);
}
