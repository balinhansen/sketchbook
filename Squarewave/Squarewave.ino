// This sketch generates square wave tones from a list of 
// frequencies stored in an array. My guess was that these 
// pitches were supported to be an 88-key keyboard

// I'd guess this script didn't support polyphony



double keys[88]={27.50, 29.13, 30.86, 32.70, 34.64, 36.70, 38.89, 
41.20, 43.65, 46.24, 48.99, 51.91, 55.00, 58.27, 61.73, 65.40, 
69.29, 73.41, 77.78, 82.40, 87.30, 92.49, 97.99, 103.82, 110.00, 
116.54, 123.47, 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 
184.99, 195.99, 207.65, 220.00, 233.08, 246.94, 261.62, 277.18, 
293.66, 311.12, 329.62, 349.22, 369.99, 391.99, 415.30, 440.00, 
466.16, 493.88, 523.25, 554.36, 587.33, 622.25, 659.25, 698.45, 
739.98, 783.99, 830.60, 880.00, 932.32, 987.76, 1046.50, 1108.73, 
1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 
1760.00, 1864.66, 1975.53, 2093.00, 2217.46, 2349.32, 2489.02, 
2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 
3951.07, 4186.01};

long start = micros();
int note=0;

void setup(){
  int i;
  double tw, a ,f;
  
 pinMode(11, OUTPUT);
 for (i=0;i<63;i++){
   tw=pow(double(2),double(1)/double(12));
   a=pow(tw,double(i));
   f=a*double(55);
   
//  keys[i]=f;
  
 }
}

int tone_in_hz(double f){
  return int(double(1000000)/double(f*2)); 
}

void loop(){
  long m=micros();
  int d;
  
  if ((m-start) > 500000){
    start=m-(m%500000);
    note++;
    if (note > 88){
     note=0; 
    }
  }
  
  d=tone_in_hz(keys[note]);
  
  digitalWrite(11,HIGH);
  delayMicroseconds(d);
  digitalWrite(11,LOW);
  delayMicroseconds(d);
}
