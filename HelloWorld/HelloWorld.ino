
#define PIN_LED 5

void setup() {
  //Enable serial output
  Serial.begin(9600);
  
  //Enable LED pin output
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
}

void loop() {
  static byte loopCount;
  static byte ledState;
  
  //Write a message
  Serial.print("HelloArduino ");
  Serial.print(loopCount++);
  Serial.println();
  
  //Toggle an LED
  if (ledState) {
    ledState = LOW;
  } else {
    ledState = HIGH;
  }
  digitalWrite(PIN_LED, ledState);
  
  //Wait 1 second
  delay(1000);
}
