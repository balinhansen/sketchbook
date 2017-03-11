const int Rpin=0;
const int Gpin=1;
const int Bpin=2;

int state=0;

void setup(){
  pinMode(Rpin,OUTPUT);
  pinMode(Gpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
}

void loop(){
  
  if (state == 0 || state == 1 || state == 5){
    digitalWrite(Rpin, HIGH);
  }else{
    digitalWrite(Rpin, LOW);
  }
  
  if (state == 1 || state == 2 || state == 3){
    digitalWrite(Gpin, HIGH);
  }else{
    digitalWrite(Gpin, LOW);
  }
  
  if (state == 3 || state == 4 || state == 5){
    digitalWrite(Bpin,HIGH);
  }else{
    digitalWrite(Bpin,LOW);
  }
  
  state++;
  
  if (state >5){state=0;}
  
  delay(33);
  //delayMicroseconds(99000);
  /*
  digitalWrite(Rpin,LOW);
  digitalWrite(Gpin,LOW);
  digitalWrite(Bpin,LOW);
  
  delay(166);
  */
  //delayMicroseconds(000);

}
