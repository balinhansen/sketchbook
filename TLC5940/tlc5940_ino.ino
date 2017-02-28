#include "Color.h";

#define DEBUG      1 // DEBUG counter; if set to 1, will write values back via serial

//How many of the shift registers - change this
#define number_of_tlc5940s 1
#define RegisterSize number_of_tlc5940s * 192

boolean registers[16][12]={ 
 {0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1}, 
 {0,0,0,0,0,0,0,0,0,0,0,1}, 
 {0,0,0,0,0,0,0,0,0,0,0,1}, 
 {0,0,0,0,0,0,0,0,1,0,0,0}, 
 {0,0,0,0,0,0,0,0,1,0,0,0}, 
 {0,0,0,0,0,0,0,0,1,0,0,0}, 
 {0,0,0,0,0,1,0,0,0,0,0,0}, 
 {0,0,0,0,0,1,0,0,0,0,0,0}, 
 {0,0,0,0,0,1,0,0,0,0,0,0}, 
 {0,0,1,0,0,0,0,0,0,0,0,0}, 
 {0,0,1,0,0,0,0,0,0,0,0,0}, 
 {0,0,1,0,0,0,0,0,0,0,0,0}, 
 {1,0,0,0,0,0,0,0,0,0,0,0}, 
 {1,0,0,0,0,0,0,0,0,0,0,0}, 
 {1,0,0,0,0,0,0,0,0,0,0,0} 
};

rgb gradient[7]={
  {255,0,0},
  {255,255,0},
  {0,255,0},
  {0,255,255},
  {0,0,255},
  {255,0,255},
  {255,0,0},
};


//rgb gradient[3]{{255,255,255},  {0,0,0},  {255,255,255}};

int GS_Pin = 3;
int SIN_Pin = 4;
int SCL_Pin = 5;
int LAT_Pin = 6;
int BLK_Pin = 7;

void setup() {
  //Serial.begin(19200); 
  pinMode(GS_Pin, OUTPUT);
  pinMode(SIN_Pin, OUTPUT);
  pinMode(SCL_Pin, OUTPUT);
  pinMode(LAT_Pin, OUTPUT);
  pinMode(BLK_Pin, OUTPUT);
  
  digitalWrite(GS_Pin,LOW);
  digitalWrite(SIN_Pin,LOW);
  digitalWrite(SCL_Pin,LOW);
  digitalWrite(LAT_Pin,LOW);
  digitalWrite(BLK_Pin,HIGH);
  
  digitalWrite(SCL_Pin, HIGH);
  digitalWrite(SCL_Pin, LOW);
}


rgb ColorFromGradient(rgb gr[], int s, float fl){
  rgb ret;
  float c=float(fl) * ( float(s) - 1.0f );

  float fade=c-floor(c);
  
  int set=int(c);
  float redVal, grnVal, bluVal;
  redVal=float(gr[set].r)-(float(gr[set].r)-float(gr[set+1].r))*fade;
  grnVal=float(gr[set].g)-(float(gr[set].g)-float(gr[set+1].g))*fade;
  bluVal=float(gr[set].b)-(float(gr[set].b)-float(gr[set+1].b))*fade;
  ret.r=int(redVal);
  ret.g=int(grnVal);
  ret.b=int(bluVal);
  return ret;
};

int count=0;

void loop() {
  int i, j, t;
  int res=10000;
  count++;
  
  if (count>res){
    count=0;
  }
  
  //Serial.println(int(float(sizeof(gradient))/float(sizeof(rgb))));
  rgb col=ColorFromGradient(gradient,int(float(sizeof(gradient))/float(sizeof(rgb))),float(count)/float(res));
  int d;
  
  unsigned int p;
  unsigned int bo;
  unsigned int m;
  unsigned int f;
  
  for (i=0;i<16;i++){
    if ((i%3)==0){p=col.r;}
    if ((i%3)==1){p=col.g;}
    if ((i%3)==2){p=col.b;}
    
    for (j=0;j<12;j++){
      registers[i][j]=0;    
    }
    for (j=0;j<4;j++){
      m=1<<j;
      f=p&m;
      bo=f>>j;
      registers[i][8+(3-j)]=boolean(bo);
    }
    
    for (j=4;j<8;j++){
      m=1<<j;
      f=p&m;
      bo=f>>j;
      registers[i][4+(3-(j-4))]=boolean(bo);
    }
  }
  
  for (i=0;i<16;i++){    
  for (j=0;j<12;j++){    
    if (registers[i][j]){
      digitalWrite(SIN_Pin, HIGH);
    }else{
      digitalWrite(SIN_Pin, LOW);
    }
    digitalWrite(SCL_Pin, HIGH);
    digitalWrite(GS_Pin,HIGH);
    digitalWrite(GS_Pin,LOW);
    digitalWrite(SCL_Pin, LOW);
  //  digitalWrite(SIN_Pin, LOW);
  }
  } 

  for (i=192;i<4096;i++){
    digitalWrite(GS_Pin,HIGH);
    digitalWrite(GS_Pin,LOW);
  }

  digitalWrite(BLK_Pin,HIGH);
  digitalWrite(LAT_Pin,HIGH);
  digitalWrite(LAT_Pin,LOW);
  digitalWrite(BLK_Pin,LOW);
  //delay(3000);
}

