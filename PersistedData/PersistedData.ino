#include <EEPROM.h>
//EEPROM Address for value
const int address = 0;

volatile unsigned int userValue;
volatile boolean promptUser = true;
volatile boolean entryComplete = false;
//Enable this to turn on terminal echo
boolean characterEcho = true;

void setup() {
  //Set up the serial port
  Serial.begin(9600);
  resetValues();
}

void loop() {
  //Write the prompt
  if (promptUser) {
    Serial.print("\nThe last saved value was ");
    Serial.print(EEPROM.read(address));
    Serial.println();
    Serial.print("Enter a value to save: ");
    promptUser = false;
  }
  
  //Save the user entry
  if (entryComplete) {
    if (userValue > 254) {
      userValue = 254;
    }
    Serial.print("\nSaving ");
    Serial.print(userValue);
    Serial.println(" to EEPROM\n");
    
    EEPROM.write(address, userValue);
    
    resetValues();
  }
}

void serialEvent() {
  int digit;
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    //Echo back to the terminal, if enabled
    if (characterEcho) {
      Serial.write(inChar);
    }
    
    //Once we hit a return, flag the main loop
    if (inChar == '\n' || inChar == '\r') {
      entryComplete = true;
      return;
    }
    
    //Add the new digit to our total
    digit = isDigit(inChar);
    if (digit >= 0) {
      userValue = (userValue * 10) + digit;
    } else {
      userValue = 0;
    } 
  }
}

void resetValues() {
  userValue = 0;
  entryComplete = false;
  promptUser = true;
}

int isDigit(char value) {
  if (value >= '0' && value <= '9') {
    return value - '0';
  } else {
    Serial.print(value);
    Serial.print(" out of range\n");
    return -1;
  }
}
