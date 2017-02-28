int servo_pin=4;
unsigned long start,pc,last;
unsigned long s_lo=17,s_hi=s_lo+69;

void setup() {
  start=micros();
  pinMode(4,OUTPUT);
  pc=random(s_lo,s_hi);
  //pc=s_lo;
  //Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop(){
  unsigned long pulseon,pulseoff;
  
  if ((micros()-last) > 500000){
    last=last+500000;
    pc=random(s_lo,s_hi);
   // pc=s_lo+((micros()/500000)%(s_hi-s_lo));
  }
  
  pulseon=((1500U*pc)/100);
  pulseoff=((1500U*(100-pc))/100);
  /*
  Serial.print(pc);
  Serial.println("");
  Serial.print(pulseon);
  Serial.println("");
  Serial.print(pulseoff);
  Serial.println("");
  Serial.println("");
  */
  
  while (micros()-start < pulseon);
  digitalWrite(4,LOW);
  start=start+pulseon;
  
  while (micros()-start < pulseoff+1500);
  digitalWrite(4,HIGH);
  start=start+pulseoff+1500;
}
