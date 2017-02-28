
#define DEBUG      1 // DEBUG counter; if set to 1, will write values back via serial

//How many of the shift registers - change this
#define number_of_74hc595s 1 
#define number_of_74hc164s 3 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8 + number_of_74hc164s * 8

boolean registers[numOfRegisterPins];
int SER_Pin = 7;   //pin 14 on the 75HC595
int RCLK_Pin = 6;  //pin 12 on the 75HC595
int SRCLK_Pin = 5; //pin 11 on the 75HC595

int main_delay=0; // ms

void setup() {  
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  
  //reset all register pins
  clearRegisters();
  writeRegisters();
}

int count=0;

void loop() {
  int i, q;
 count++;

  for (i=0;i<32;i++){
      setRegisterPin(i,HIGH);
  }
  
  //clearRegisters();  

  writeRegisters();
 
  if (main_delay > 0){
    delay(main_delay);
  }
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

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
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


