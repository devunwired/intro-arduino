String inputString = "";
boolean promptUser = true;
boolean stringComplete = false;
//Enable this to turn on terminal echo
boolean characterEcho = true;

void setup() {
  //Set up the serial port
  Serial.begin(9600);
  //Reserve some memory for the input string
  inputString.reserve(512);
}

void loop() {
  //Write the prompt
  if (promptUser) {
    Serial.print("What is your name? ");
    promptUser = false;
  }
  
  //Print the response
  if (stringComplete) {
    Serial.print("\nNice to meet you ");
    Serial.println(inputString);
    
    inputString = "";
    stringComplete = false;
    promptUser = true;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    //Echo back to the terminal, if enabled
    if (characterEcho) {
      Serial.write(inChar);
    }
    
    //Add the new character to the buffer
    inputString += inChar;
    //Once we hit a return, flag the main loop
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    } 
  }
}
