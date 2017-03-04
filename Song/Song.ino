#define PIEZO 11

int bpm=160;
double pitch[120];


int notes[5]={49,53,54,46,44};

int beats[5]={16,8,8,16,16};
int beatcount=0;
  
  
double freq_from_midi(int midinote){
  int normalized_note;
  normalized_note = midinote-57;
  double twel=pow(2,double(1)/double(12));
  double freq = pow(twel,float(normalized_note))*880;
  return freq;
}

void setup(){
  int i;
  
  Serial.begin(115200);
  
  pinMode(PIEZO,OUTPUT);
  Serial.print("Size of beats");
  Serial.println(sizeof(beats));
  
  for (i=0;i<sizeof(beats)/2;i++){
    beatcount+=beats[i]; 
  }
  
  for (i=0;i<120;i++){
    pitch[i]=freq_from_midi(i); 
  }
}

int whichbeat(int n){
  int i=0;
  while (n>=0){
    n-=beats[i];
    i++;
  }
  return i-1;
}

void superdelay(unsigned long duration){
  unsigned long now=micros(), then=now+duration;
  
  while (micros() < then);
}

void loop(){
  unsigned long count;
  double pulse;
  count=(micros()/100000)%(beatcount);
  
  pulse=1000000/pitch[notes[whichbeat(count)]];
  /*
  Serial.print(whichbeat(count));
  Serial.print(" ");
  Serial.print(count);
  Serial.print(" ");
  Serial.print(freq_from_midi(notes[whichbeat(count)]));
  Serial.print(" ");
  Serial.println(pulse);
  */
  
  digitalWrite(PIEZO,HIGH);
  delayMicroseconds(pulse);
  digitalWrite(PIEZO,LOW);
  delayMicroseconds(pulse);
}


