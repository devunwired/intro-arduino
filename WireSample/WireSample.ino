#include <Wire.h>

#define  JOY_nINT       A10     // active low interrupt input
#define  JOY_nRESET     A11     // active low reset output

void setup()
{
  Serial.begin(115200);
  
  init_joystick(10);
}

void loop()
{
  char msg[16];
  int x, y;
  
  read_joystick(&x, &y);
  x = constrain(x, -128, 127);
  y = constrain(y, -128, 127);
  
  Serial.print('\r');
  sprintf(msg, "X: %4d Y: %4d", x, y);
  Serial.print(msg);
  
  delay(20);
}

// ===================================
// Austria Microsystems i2c Joystick
// Mfg. P/N: N50P111
void init_joystick(int threshold)
{
  byte status = 0;

  pinMode(JOY_nINT, INPUT);
  digitalWrite(JOY_nINT, HIGH);

  pinMode(JOY_nRESET, OUTPUT);

  digitalWrite(JOY_nRESET, 1);
  delay(1);
  digitalWrite(JOY_nRESET, 0);
  delay(1);
  digitalWrite(JOY_nRESET, 1);

  Wire.begin();

  do {
    status = read_joy_reg(0x0f);
  } while ((status & 0xf0) != 0xf0);

  // invert magnet polarity setting, per datasheet
  write_joy_reg(0x2e, 0x86);

  calibrate_joystick(threshold);
}

int offset_X, offset_Y;

void calibrate_joystick(int dz)
{
  char iii;
  int x_cal = 0;
  int y_cal = 0;

  // Low Power Mode, 20ms auto wakeup
  // INTn output enabled
  // INTn active after each measurement
  // Normal (non-Reset) mode
  write_joy_reg(0x0f, 0x00);
  delay(1);

  // dummy read of Y_reg to reset interrupt
  read_joy_reg(0x11);

  for(iii = 0; iii != 16; iii++)
  {
    while(!joystick_interrupt()) {}

    x_cal += read_joy_reg(0x10);
    y_cal += read_joy_reg(0x11);
  }

  // divide by 16 to get average
  offset_X = -(x_cal>>4);
  offset_Y = -(y_cal>>4);

  write_joy_reg(0x12, dz - offset_X);  // Xp, LEFT threshold for INTn
  write_joy_reg(0x13, -dz - offset_X);  // Xn, RIGHT threshold for INTn
  write_joy_reg(0x14, dz - offset_Y);  // Yp, UP threshold for INTn
  write_joy_reg(0x15, -dz - offset_Y);  // Yn, DOWN threshold for INTn

  // dead zone threshold detect requested?
  if (dz)
  {
    write_joy_reg(0x0f, 0x04);
  }
}

void read_joystick(int *x, int *y)
{
  *x = read_joy_reg(0x10) + offset_X;
  *y = read_joy_reg(0x11) + offset_Y;  // reading Y clears the interrupt
}

char joystick_interrupt()
{
  return digitalRead(JOY_nINT) == 0;
}

#define  JOY_I2C_ADDR    0x40

char read_joy_reg(char reg_addr)
{
  char c;

  Wire.beginTransmission(JOY_I2C_ADDR);
  Wire.write(reg_addr);
  Wire.endTransmission();

  Wire.requestFrom(JOY_I2C_ADDR, 1);

  while(Wire.available())
  {
    c = Wire.read();
  }

  return c;
}

void write_joy_reg(char reg_addr, char val)
{
  Wire.beginTransmission(JOY_I2C_ADDR);
  Wire.write(reg_addr);
  Wire.write(val);
  Wire.endTransmission();
}
