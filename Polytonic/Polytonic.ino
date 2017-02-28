int music_pins[4]={0,1,2,4};
int num_pins=4;
//int music_pins[8]={3,4,5,6,7,8,9,10};
//int tones[8]={55,110,220,440,880,1760,3520,7040};
//int tones[8]={697,770,852,941,1209,1336,1477,1633}; // touchtone
//int tones[8]={55, 58, 61, 65, 69, 73, 77, 82}; // some notes
//int tones[8]={110, 116, 123, 130, 138, 146, 155, 164};
//int tones[8]={116, 138, 155, 184, 207, 233, 277, 311};
int tones[5]={116, 155, 207, 311};


int state[8]={0,0,0,0,0,0,0,0};
unsigned long start[8];


void setup(){
  int i;
  for (i=0;i<num_pins;i++){
    start[i]=micros();
    pinMode(music_pins[i], OUTPUT);
  }
 // Serial.begin(9600);
}

double tone_in_hz(double f){
  if (f==0){f=1;}
  return (double(1000000)/double(f*2)); 
}

unsigned long ul_tone(unsigned long f){
  if (f!=0){
    return 1000000U/(f*4); 
  }else{
    return 0;
  }
}

void loop(){
  unsigned long a,b,d;
  int i;
  
  for (i=0;i<num_pins;i++){
    d=ul_tone(tones[i]);
    if (micros()-start[i] > d){
      if (state[i]){
        digitalWrite(music_pins[i],LOW);
        state[i]=0;
      }else{
        digitalWrite(music_pins[i],HIGH);
        state[i]=1;
      }
      start[i]=start[i]+d;
    }
  }
}
