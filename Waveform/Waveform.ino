#define NUM_BUFFERS 8
#define SAMPLE_SIZE 117

unsigned long peaks[NUM_BUFFERS]={};
unsigned int mics[SAMPLE_SIZE]={};
unsigned long lag=120;
int debug=0;

int thresh=15;

void setup(){
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
  
  if (debug){
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
  then=s+SAMPLE_SIZE*lag;
  
  while (micros() < then){
    mics[i]=micros()-s;
    for (j=0;j<15;j++){
      peaks[i]+=(analogRead(A0)>thresh);
      peaks[i]<<=1;
    }
    peaks[i]+=(analogRead(A0)>thresh);
    i++;
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
  then=s+SAMPLE_SIZE*lag;
  
  i=0;
  l=0;
  
  while (micros()<then){
    
     l=i%(SAMPLE_SIZE);
     if (micros()>s+mics[l]){
       
       for (j=15;j>-1;j--){
           p=peaks[int(floor(l/16))];
           if ((p>>j)&0x1){
             digitalWrite(11,HIGH);
             
  if (debug){Serial.print("1");}
           }else{
             digitalWrite(11,0);
             
  if (debug){Serial.print("0");}
           }
       }
       i++;
       
  if (debug){Serial.println();}
     }
  }
 
  if (debug){ Serial.println();}
  
  for (i=0;i<NUM_BUFFERS;i++){
    peaks[i]=0;
  }
  for (i=0;i<SAMPLE_SIZE;i++){
    mics[i]=0;
  }
  
  f=micros();
  //lag = (f-s)/SAMPLE_SIZE; 
  
  
  if (debug){Serial.println(lag);}
  
}
