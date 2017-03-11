#include <SoftwareSerial.h>

SoftwareSerial myser(3,4);
  
const int Rpin=0;
const int Gpin=1;
const int Bpin=2;

struct color{
 float r;
 float g;
 float b;
};

int FadePins[3]={Rpin,Gpin,Bpin};
unsigned long FadeStat[3]={0,0,0};


double res, rep,pwmlen;

float brightness=0.05;

int states=12; // PWM levels 2^states
  
unsigned long start,last=0,pwm=0,s;

unsigned long duration=15*1000000;
int count;

color gradient[6]=
{{1,0,0},
{1,1,0},
{0,1,0},
{0,1,1},
{0,0,1},
{1,0,1}};



void superDelay(unsigned long t){
  int d,m,i;
  start=micros();
  while (micros()<start+t);
}


void setup(){
  myser.begin(9600);
  unsigned long f;
  
  start=micros();
  
  pinMode(Rpin,OUTPUT);
  pinMode(Gpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
  
  f=micros();
  digitalWrite(Rpin,LOW);
  digitalWrite(Gpin,LOW);
  digitalWrite(Bpin,LOW);
  s=micros()-f;
  
  count=(sizeof(gradient)/12);
  
  res=double(duration)/double(count*100*(1<<states));
  rep=res/(1<<states);
  pwmlen=double(res)/double(rep);
  pwm=pwmlen;
  last=res;
  
  start=micros();
}

void loop(){
  int c,i;
  unsigned long now=micros(),syn=now,fin;
  unsigned long curtime=(now-start)%duration;
  
  double span=floor(double(duration)/double(count))+1;
  int stage = double(curtime)/span;
  
  float phase=float(double(curtime-(span*stage))/double(span));
  
  c=floor(stage);
  color a=gradient[c];
  color b=gradient[c];
  
  if (c>=count-1){
    b=gradient[0];
  }else{
    b=gradient[c+1];
  }
  
  FadeStat[0]=(a.r-((a.r-b.r)*phase))*pwmlen+now;
  FadeStat[1]=(a.g-((a.g-b.g)*phase))*pwmlen+now;
  FadeStat[2]=(a.b-((a.b-b.b)*phase))*pwmlen+now;
   
  fin=now+pwmlen;
  
  digitalWrite(Rpin,HIGH);
  digitalWrite(Gpin,HIGH);
  digitalWrite(Bpin,HIGH);

  
  /*
  myser.print(now);
  myser.print(",");
  myser.print(fin);
  myser.print(" ");
  myser.print(FadeStat[0]);
  myser.print(",");
  myser.print(FadeStat[1]);
  myser.print(",");
  myser.print(FadeStat[2]);
  myser.print(" ");
  myser.println(micros());
  */
  
  while (micros()<fin){
    syn=micros();
    if (syn>FadeStat[0]){
      digitalWrite(Rpin,LOW);
    }
    
    if (syn>FadeStat[1]){
      digitalWrite(Gpin,LOW);
    }
    
    if (syn>FadeStat[2]){
      digitalWrite(Bpin,LOW);
    }
  }
}
