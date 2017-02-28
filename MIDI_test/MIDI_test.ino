#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);

unsigned char buffer;

void setup(){
  Serial.begin(115200);
  mySerial.begin(31250);
  
}

void loop(){
  unsigned long msg=0;
  cli();
  
  if (mySerial.available()){
    msg=mySerial.read();
    
    Serial.print("Message=");
    Serial.println(msg,BIN);
    
    if (msg==0){
      Serial.println();
    }
/*
    if (msg & 0x80){
      
      Serial.print("Status: ");
      Serial.print(msg>>4 & 0x8);
      Serial.print(" Channel=");
      Serial.print(msg & 0x7,DEC);
      Serial.print(" ");
    }else{
      Serial.print("Data: ");
      Serial.print(msg,DEC);
      Serial.print(" ");
    }
    */
  }
}
