#include <SPI.h>

void setup(){
  Serial.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE1);
  
  SPI.transfer(0x60); SPI.transfer(0b00011111);
  SPI.transfer(0x62); SPI.transfer(0x00); //0x08 for i2c
  SPI.transfer(0x63); SPI.transfer(0b11010000);

  delay(100);
}

void loop(){
  int i;
  Serial.print("Who: ");
  SPI.transfer(0x8f);
  Serial.print(SPI.transfer(0xff));
  Serial.println("");
}
