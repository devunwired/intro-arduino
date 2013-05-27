#include <MsTimer2.h>

#define BUTTON A7

const int kDebounceInterval = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  static byte b1 = HIGH;
  byte b;
  
  b = digitalRead(BUTTON);
  if (b1 != b) {
    b1 = b;
    if (b1 == LOW) {
      MsTimer2::set(kDebounceInterval, buttonTrigger);
      MsTimer2::start();
    } else {
      MsTimer2::stop();
    }
  }
}

void buttonTrigger() {
  Serial.println("Button Trigger");
  
  //Cancel timer
  MsTimer2::stop();
}
