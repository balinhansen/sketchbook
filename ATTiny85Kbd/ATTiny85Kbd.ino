#include <SoftwareSerial.h>
#include <PS2Keyboard.h>

const int Rx = 3;
const int Tx = 4;

SoftwareSerial mySerial(Rx,Tx);
  
void setup(){
  //Serial.begin(115200);
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  mySerial.begin(9600);
  
  
}

void loop(){
  
  mySerial.println("Blah!");
  delay(1000);
 
}
