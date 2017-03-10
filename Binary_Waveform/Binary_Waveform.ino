#define NUM_BUFFERS 1

unsigned long peaks[NUM_BUFFERS]={};
unsigned long lag=120;
int debug=0;
int showlag=0;

int thresh=15;

void setup(){
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
  
  if (debug || showlag){
    Serial.begin(115200);
  }
}

void loop(){
  int i=0,j=0,l;
  
  unsigned long p;
  
  unsigned long then;
  unsigned long s, f;
  
  i=0;
  
  s=micros();
  
  for (i=0;i<NUM_BUFFERS;i++){
    //mics[i]=micros()-s;
    for (j=0;j<15;j++){
      peaks[i]+=(analogRead(A0)>thresh);
      peaks[i]<<=1;
    }
    peaks[i]+=(analogRead(A0)>thresh);
  }
  
  f=micros();
  lag = (f-s);
  if (debug || showlag){
    Serial.print("Record lag: ");
    Serial.println(lag);
}
  
  
  if (debug){
    for (i=0;i<NUM_BUFFERS;i++){
      Serial.println(peaks[i],BIN); 
    }
    Serial.println();
  }
  
  //Serial.println(peaks[i],BIN);
  
  if (debug){delay (300);}
  
 
  s=micros();
  i=0;
  l=0;
  
 for (i=0;i<NUM_BUFFERS;i++){
   for (j=15;j>-1;j--){
       p=peaks[i];
       if ((p>>j)&0x1){
         digitalWrite(11,HIGH);
          if (debug){Serial.print("1");}
       }else{
         digitalWrite(11,0);
          if (debug){Serial.print("0");}
       }
          delayMicroseconds(10);
   }
  if (debug){Serial.println();}
  }
 
  if (debug){ Serial.println();}
  
  for (i=0;i<NUM_BUFFERS;i++){
    peaks[i]=0;
  }
  
  f=micros();
  lag = (f-s);
  
  
  if (debug || showlag){
  Serial.print("Play lag: ");
    Serial.println(lag);
    Serial.println();
}
  
  if (debug){delay(1000);}
  
}
