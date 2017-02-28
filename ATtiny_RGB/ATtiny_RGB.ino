/*

// Wrote this Code back in 2013 before I knew how to do 
// anything with ATtiny so obviously the pins are for Arduino 
// Uno in spite of the name of this file. 

// I think I remember this code being better than the color 
// fader I wrote for actual ATtiny85s in 2015

*/

//#include "pins_arduino.h" 

#define redPin       11
#define grnPin      10
#define bluPin     9
#define DEBUG      1 // DEBUG counter; if set to 1, will write values back via serial

//How many of the shift registers - change this
#define number_of_74hc595s 1 
#define number_of_74hc164s 3 
#define number_of_tlc5940s 1

int tick_count=0;

//do not touch
#define numOfRegisterPins 32 //number_of_74hc595s * 8 + number_of_74hc164s * 8 + number_of_tlc5940s * 192

boolean registers[numOfRegisterPins];
int RCLK_Pin = 5;  //pin 12 on the 75HC595
int SRCLK_Pin = 6; //pin 11 on the 75HC595
int SER_Pin = 7;   //pin 14 on the 75HC595
int LTCH_Pin = 3;  // pin x on the TLC5940

int BLK_Pin = 10;   // pin x on the TLC5940
int GSCLK_Pin = 9; // pin x on the TLC5940


int pingDistance = 0;
int maxDistance = 30000; // 30,000x40ms = 2400x500ms = 20min
int main_delay=45; // 40ms

unsigned int flashCounter = 0;
boolean ledStatus = false;

int gradient[7][3]={
  {255,0,0},
  {255,255,0},
  {0,255,0},
  {0,255,255},
  {0,0,255},
  {255,0,255},
  {255,0,0},
};

void setup() {  
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(BLK_Pin, OUTPUT);
  pinMode(LTCH_Pin, OUTPUT);
  
 // Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(grnPin, HIGH);
  digitalWrite(bluPin, HIGH);
  digitalWrite(redPin, HIGH);
  
  digitalWrite(LTCH_Pin,LOW);
  digitalWrite(BLK_Pin,HIGH);
  
  //reset all register pins
  clearRegisters();
  writeRegisters();
}

int count=0;

void loop() {
  int traffic_ticks;
  tick_count++;
  
  int i;
  int q;
  
  pingDistance+=1;
  if (pingDistance > maxDistance){
    pingDistance = 0;
  }
  float color=(float(pingDistance) / float(maxDistance))*((float(sizeof(gradient))/6.0f)-1.0f);
  float fade=color-float(int(color));
  
 int set=int(color);
 float redVal, grnVal, bluVal;
 redVal=float(gradient[set][0])-(float(gradient[set][0])-float(gradient[set+1][0]))*fade;
 grnVal=float(gradient[set][1])-(float(gradient[set][1])-float(gradient[set+1][1]))*fade;
 bluVal=float(gradient[set][2])-(float(gradient[set][2])-float(gradient[set+1][2]))*fade;
 int r,g,b;
 r=int(redVal);
 g=int(grnVal);
 b=int(bluVal);
 // Convert to 0-255
  
// if ((count % 10)==0){
 /*
 Serial.print("color: ");
   Serial.print(color,DEC);
   Serial.print(" set: ");
   Serial.print(int(color),DEC);
   Serial.print(" fade: ");
   Serial.print(int(fade));
   Serial.print(" R: ");
   Serial.print(r);
   Serial.print(" G: ");
   Serial.print(g);
   Serial.print(" B: ");
   Serial.println(b);
//   count=0;
*/

  if (pingDistance !=0){
    analogWrite(redPin, r);   // Write current values to LED pins
    analogWrite(grnPin, g);      
    analogWrite(bluPin, b); 
  }
  for (i=0;i<numOfRegisterPins;i++){
    q = rand();
    q=q&1;
    if (q){
      setRegisterPin(i,HIGH);
    }else{
      setRegisterPin(i,LOW);
    }
  }
  
  //clearRegisters();  
  if (float(redVal/255)>0.5f){setRegisterPin(7, HIGH);setRegisterPin(30, HIGH);}else{setRegisterPin(7,LOW);setRegisterPin(30,LOW);}
  if (float(grnVal/255)>0.5f){setRegisterPin(6, HIGH);setRegisterPin(29, HIGH);}else{setRegisterPin(6,LOW);setRegisterPin(29,LOW);}
  if (float(bluVal/255)>0.5f){setRegisterPin(5, HIGH);setRegisterPin(31, HIGH);}else{setRegisterPin(5,LOW);setRegisterPin(31,LOW);}
  
  traffic_ticks=tick_count%int(float(10000)/float(main_delay));
  
  if (traffic_ticks<int(float(5000)/float(main_delay))){
    setRegisterPin(4,HIGH);
    setRegisterPin(3,LOW);
    setRegisterPin(2,LOW);
  }
  if (traffic_ticks>=int(float(5000)/float(main_delay)) && traffic_ticks<int(float(9000)/float(main_delay))){
    setRegisterPin(2,HIGH);
    setRegisterPin(4,LOW);
    setRegisterPin(3,LOW);
  }
  if (traffic_ticks>=int(float(9000)/float(main_delay)) && traffic_ticks<int(float(10000)/float(main_delay))){
    setRegisterPin(3,HIGH);
    setRegisterPin(2,LOW);
    setRegisterPin(4,LOW);
  }
  if (traffic_ticks>=10000){
    tick_count=0;
  }
  //setRegisterPin(5,HIGH);
  //setRegisterPin(6,HIGH);
  //setRegisterPin(7,HIGH);

  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
  
 
  delay(main_delay);
}

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){
  int i;
  
  digitalWrite(RCLK_Pin, LOW);
  
  for(i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);
  
}


//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}


