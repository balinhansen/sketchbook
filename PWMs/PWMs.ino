#define PIEZO 11


double freq_from_midi(int midinote){
  int normalized_note;
  normalized_note = midinote-57;
  double twel=pow(2,double(1)/double(12));
  double freq = pow(twel,float(normalized_note))*440;
  return freq;
}

void setup(){
  Serial.begin(115200);
  
  pinMode(PIEZO,OUTPUT);
}

void superdelay(unsigned long duration){
  unsigned long now=micros(), then=now+duration;
  
  while (micros() < then);
}

void loop(){
  unsigned long count;
  double pulse;
  
  count=(micros()/2000000)%120;
  pulse=1000000/freq_from_midi(count);
  
  Serial.print(count);
  Serial.print(" ");
  Serial.print(freq_from_midi(count));
  Serial.print(" ");
  Serial.println(pulse);
  
  digitalWrite(PIEZO,HIGH);
  superdelay(pulse);
  digitalWrite(PIEZO,LOW);
  superdelay(pulse);
}


