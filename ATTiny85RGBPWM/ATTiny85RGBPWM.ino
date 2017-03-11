const int Rpin=0;
const int Gpin=1;
const int Bpin=2;

int state=0;
int states=10;
unsigned long phase;
  
unsigned long start,s,f;

void superDelay(unsigned long t){
  int d,m,i;
  start=micros();
  while (micros()<start+t);
}


void setup(){
  pinMode(Rpin,OUTPUT);
  pinMode(Gpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
  
  f=micros();
  digitalWrite(Rpin,LOW);
  digitalWrite(Gpin,LOW);
  digitalWrite(Bpin,LOW);
  s=micros()-f;
  
  phase=1000000/s;
}

void loop(){
  unsigned long now=micros();
  
  state++;
  
  if (state >= (1<<(states-1))){state=0;}
  
  digitalWrite(Rpin,HIGH);
  digitalWrite(Gpin,HIGH);
  digitalWrite(Bpin,HIGH);
  
  superDelay(s*state); // state);
  
  digitalWrite(Rpin,LOW);
  digitalWrite(Gpin,LOW);
  digitalWrite(Bpin,LOW);
  
  superDelay(s* ( (1<<states-1) - state)); //(1<<(states-1))-state);

}
