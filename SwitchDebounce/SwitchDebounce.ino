//We are including an external library
#include <MsTimer2.h>

#define BUTTON A7
#define LED 5

const int kDebounceInterval = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, HIGH);
}

void loop() {
  static byte b1 = HIGH;
  byte b;
  
  //Check if the current button state has changed
  b = digitalRead(BUTTON);
  if (b1 != b) {
    b1 = b;
    if (b1 == LOW) {
      //Set a timer to go off if the button is still pressed
      MsTimer2::set(kDebounceInterval, buttonTrigger);
      MsTimer2::start();
    } else {
      //On button release, reset the timer
      MsTimer2::stop();
      digitalWrite(LED, HIGH);
    }
  }
}

/*
 * Function called when the debounce timer expires
 */
void buttonTrigger() {
  Serial.println("Button Trigger");
  digitalWrite(LED, LOW);
  
  //Cancel timer
  MsTimer2::stop();
}
