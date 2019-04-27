/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int brk=1000;
int pus=200;
int srt=200;
int lng=500;
int spc=3000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(brk);               // wait for a second
  
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(lng);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(lng);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(lng);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(brk);
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(pus);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(srt);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(spc);               // wait for a second
  
}
