#include <TempSensor.h>
#include <LightSensor.h>
#include <RgbLed.h>

#define  RELAY1  A0
#define  RELAY2  A1

RgbLed Led1(8, 10, 9);
RgbLed Led2(5, 7, 6);
RgbLed Led3(2, 4, 3);

LightSensor Light(A2);
TempSensor Temp(A3);

void setup() {
  Serial.begin(115200);
  
  init_relays();
}

void loop() {
  static byte coolState, heatState;
  
  //Enable the output LED based on luminance
  int light = Light.read();
  if (Light.isDark()) {
    Led1.setRGB(255, 255, 255);
  } else if (Light.isBright()) {
    Led1.clear();
  }
  
  //Set LED color based on current temp
  int minTemp = 65;
  int maxTemp = 85;
  int temp = constrain(Temp.read(), minTemp, maxTemp);
  int val = map(temp, minTemp, maxTemp, 0, 63);
  //Set Red/Blue as inverse of each other
  Led3.setRGB(val, 0, 63 - val);

  //Set call for heat/cooling based on thresholds
  if (temp > 80) {
    coolState = HIGH;
    heatState = LOW;
  } else if (temp < 70) {
    coolState = LOW;
    heatState = HIGH;
  } else if (temp > 73 && temp < 77) {
    coolState = LOW;
    heatState = LOW;
  }

  digitalWrite(RELAY1, coolState);
  digitalWrite(RELAY2, heatState);
  
  debug(temp, light);
  delay(20);
}

void init_relays() {
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
}

/*
 * Write current values out serial for debugging
 */
void debug(int temp, int light) {
  Serial.print('\r');
  Serial.print("Temp: ");
  Serial.print(temp, DEC);
  Serial.print(" Light: ");
  Serial.print(light, DEC); 
}
