// I have no idea what the point of this script was apart 
// from the obvious. It makes a sound on a pin ... continuously.

// Which sound? I'm not quiet sure.

int music_pin=11;
unsigned long start;
volatile int msg=0;


void setup(){
  start=micros();
  pinMode(music_pin, OUTPUT);
  attachInterrupt(0, report, CHANGE);
  Serial.begin(9600);
}

double tone_in_hz(double f){
  if (f==0){f=1;}
  return (double(1000000)/double(f)); 
}

unsigned long ul_tone(unsigned long f){
  if (f!=0){
    return 1000000U/(2*f); 
  }else{
    return 0;
  }
}

void loop(){
  unsigned long a,b,d;
  if (msg){
    Serial.print(msg);
    Serial.println("");
    msg=0;
  }
  
  b=micros();
  a=(b-(b%1000000))/1000000; //double(micros())/100000;
  d=ul_tone(1633); //d=ul_tone(a+10); //unsigned(long(tone_in_hz(double(a))));
  
  digitalWrite(music_pin, HIGH);
  while ((micros()-start) < d);
  start=start+d;
  
  digitalWrite(music_pin,LOW);
  while ((micros()-start) < d);
  start=start+d;
}

void report(){
  unsigned long a,b,d;
  b=micros();
  a=(b-(b%1000000))/1000000; //double(micros())/100000;
  msg=a+10;
}
