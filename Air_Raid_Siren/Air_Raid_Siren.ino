// OH GOD IT'S HORRIBLE

int note=0;

void setup(){
 pinMode(11, OUTPUT);
}

int tone_in_hz(double f){
  return int(double(1000000)/double(f*2)); 
}

void loop(){
  long n,m,d, hz;
  m=micros();
  n=micros();
  
  digitalWrite(11,HIGH);
 
  hz = double(m%15000000)/1440;
  
  if (hz < 3600){
    d=tone_in_hz(hz);
  }
  if (hz <= 7200 && hz >= 3600){
    d=tone_in_hz(3600);
  }
  if ( hz > 7200){
    d=tone_in_hz(3600UL-(hz-7200));
  }
  
 
  while ((n < (m + d)))
  {
    n=micros();
  }
  
  digitalWrite(11,LOW);
  
  while (n < m+d*2){
    n=micros();
  
  }
}
