#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23

int vx=A3;
int vy=A2;
int tp=A0;

// Since I won't remember A5 -> SCL, A4 -> SDA, SDO -> HI

int Addr = 105;                 // I2C address of gyro
int x, y, z;
int w;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  writeI2C(CTRL_REG1, 0x1F);    // Turn on all axes, disable power down
  writeI2C(CTRL_REG3, 0x08);    // Enable control ready signal
  writeI2C(CTRL_REG4, 0x80);    // Set scale (500 deg/sec)
  pinMode(vx,INPUT);
  pinMode(vy,INPUT);
  pinMode(tp,INPUT);
  delay(100);                   // Wait to synchronize 
}

void loop(){
  int px,py;
  int ax,ay;
  int temp;
  
  px=pulseIn(vx,HIGH);
  py=pulseIn(vy,HIGH);
  temp=analogRead(tp);
  
  ax = ((px / 10) - 500) * 8;
  ay = ((py / 10) - 500) * 8;
  
  getGyroValues();              // Get new values
  // In following Dividing by 114 reduces noise
  Serial.print("Who:"); Serial.print(w);
  Serial.print(" Gyro X:");  Serial.print(x / 114);  
  Serial.print(" Gyro Y:"); Serial.print(y / 114);
  Serial.print(" Gyro Z:"); Serial.print(z / 114);
  Serial.print(" Accel X:"); Serial.print(ax);
  Serial.print(" Accel Y:"); Serial.print(ay);
  Serial.print(" Temp:"); Serial.println(temp);
  delay(100);                   // Short delay between reads
}

void getGyroValues () {
  byte MSB, LSB;

  MSB = readI2C(0x29);
  LSB = readI2C(0x28);
  x = ((MSB << 8) | LSB);

  MSB = readI2C(0x2B);
  LSB = readI2C(0x2A);
  y = ((MSB << 8) | LSB);

  MSB = readI2C(0x2D);
  LSB = readI2C(0x2C);
  z = ((MSB << 8) | LSB);
  
  LSB = readI2C(0x0F);
  w = LSB;
  
}

int readI2C (byte regAddr) {
    Wire.beginTransmission(Addr);
    Wire.write(regAddr);                // Register address to read
    Wire.endTransmission();             // Terminate request
    Wire.requestFrom(Addr, 1);          // Read a byte
    while(!Wire.available()) { };       // Wait for receipt
    return(Wire.read());                // Get result
}

void writeI2C (byte regAddr, byte val) {
    Wire.beginTransmission(Addr);
    Wire.write(regAddr);
    Wire.write(val);
    Wire.endTransmission();
}
