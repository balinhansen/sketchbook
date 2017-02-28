/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
int readpin=7;
int reading=1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(readpin,INPUT);
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.print("Reading: ");
  Serial.print(reading);
  Serial.print(". ");

  unsigned long now=micros();
  unsigned long sampletime=1000000;
  unsigned long then=now+sampletime;
  unsigned long wavelength;
  
  int last=0;
  int sample=0;
  unsigned long count=0;
  unsigned long sps=0;
  
  last=digitalRead(readpin);
  
  while (now < then){
    sps++;
    sample=digitalRead(readpin);
    if (sample!=last){
      last=sample;
      count++;
    }
    now=micros();
  }
  
  Serial.print("Transitions: ");
  Serial.print((double)count);
  Serial.print(". Samples per Second: ");
  Serial.println(sps);
  reading++;
  
  /*
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
  */

}
