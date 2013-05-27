#define  RELAY1         A0
#define  RELAY2         A1
#define  LIGHT_SENSOR   A2
#define  TEMP_SENSOR    A3

#define  LED3_RED       2
#define  LED3_GREEN     4
#define  LED3_BLUE      3

#define  LED2_RED       5
#define  LED2_GREEN     7
#define  LED2_BLUE      6

#define  LED1_RED       8
#define  LED1_GREEN     10
#define  LED1_BLUE      9

void setup() {
  Serial.begin(115200);
  
  init_relays();
  init_leds();
}

void loop() {
  static byte coolState, heatState;
  
  //Enable the output LED based on luminance
  int light = read_light();
  if (light < 100) {
    digitalWrite(LED1_RED, LOW);
    digitalWrite(LED1_GREEN, LOW);
    digitalWrite(LED1_BLUE, LOW);
  } else if (light > 150) {
    digitalWrite(LED1_RED, HIGH);
    digitalWrite(LED1_GREEN, HIGH);
    digitalWrite(LED1_BLUE, HIGH);
  }
  
  //Set LED color based on current temp
  int minTemp = 65;
  int maxTemp = 85;
  int temp = constrain(read_temp(), minTemp, maxTemp);
  int val = map(temp, minTemp, maxTemp, 0, 63);
  analogWrite(LED3_RED, 255 - val);
  analogWrite(LED3_GREEN, 255);
  analogWrite(LED3_BLUE, 192 + val);

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

double read_temp() {
  int val = analogRead(TEMP_SENSOR);
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

int read_light() {
  int val = analogRead(LIGHT_SENSOR);
  /*
   * Arduino board contains a 10-bit analog to digital converter. This
   * will map input voltages between 0 and 5 volts into integer values
   * between 0 and 1023. This yields a resolution between readings of: 5
   * volts / 1024 units or, .0049 volts (4.9 mV) per unit.
   */
  double voltagemv = val * 4.9;
  
  /*
   * The TPS852 light sensor outputs a constant current that is linearly
   * proportional to the luminance value (in lux) of the ambient light. The
   * output is 0.35uA / lux (typical).  The demo shield passes this current
   * through a 51K resistor. VOUT = Iout * 51K, so the light coefficient
   * is 17.85 mV/lux.
   */
  double kLightCoefficientLux = 17.85;
  double light = voltagemv / kLightCoefficientLux;
  
  return light;
}

void init_relays() {
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
}

void init_leds() {
  digitalWrite(LED1_RED, 1);
  digitalWrite(LED1_GREEN, 1);
  digitalWrite(LED1_BLUE, 1);

  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);

  digitalWrite(LED2_RED, 1);
  digitalWrite(LED2_GREEN, 1);
  digitalWrite(LED2_BLUE, 1);

  pinMode(LED2_RED, OUTPUT);
  pinMode(LED2_GREEN, OUTPUT);
  pinMode(LED2_BLUE, OUTPUT);

  digitalWrite(LED3_RED, 1);
  digitalWrite(LED3_GREEN, 1);
  digitalWrite(LED3_BLUE, 1);

  pinMode(LED3_RED, OUTPUT);
  pinMode(LED3_GREEN, OUTPUT);
  pinMode(LED3_BLUE, OUTPUT);
}
