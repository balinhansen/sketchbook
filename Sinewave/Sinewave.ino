// I believe this sketch was a DDS (direct digital sythensis) 
// sine waveform generator which utilized PWM to emulate an 
// analogue wave using the digital pins.

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

double pi;
double phase;
int wave_out=11;
double f=1;
double sample=12;

void setup(){
  int i;
  double tw, a ,f;
 pi=atan(1)*4;
 phase=double(random(0,360000))/360000*2*pi;
 pinMode(wave_out, OUTPUT);
 //Serial.begin(9600);
 
  for (i=0;i<88;i++){
   tw=pow(double(2),double(1)/double(12));
   a=pow(tw,double(i));
   f=a*double(3.43);
   
  keys[i]=f;
  
 }
}

void loop(){
  unsigned long n,m,d,o,p;
  m=micros();
  n=m;
  double r,w,ph,wave;
  int t,s;
  
  f= keys[int(floor(pow(1+double(micros())/double(500000),1.01))) % 88];
  //sample=pow(10,log10(f)*-1+2);
  //Serial.print(f);
  
  digitalWrite(wave_out,HIGH);
  
  w=double(1000000)/double(f);
  
  d=long( double(1000000)/(double(f)*double(sample)) );
 
  o=((m+d)-micros());
  
  phase=(2*pi*o/w)+phase;
  while (phase > 2*pi){phase=phase-2*pi;}
  
  wave=(1+sin(phase))/2;
  p=int(double(d)*wave);
  
  while (micros() < (m+p));
  
  digitalWrite(wave_out,LOW);
  
  wave=(1+(sin(phase)*-1))/2;
  p=int(double(d)*wave);

  while (micros() < m+p);

}
