// This was a neat experiment with manual pulse width modulation 
// the idea was that LEDs would increase in brightness like a 
// droplet collecting water and the turn off like the droplet 
// had fallen off. Each pin collects and drops water at it's own 
// unique rate.


unsigned long tick;
long freq[14];
long stat[14];
int pins[] ={0,1,0,1,0,1,0,1,0,1,0,1,0,1};

void setup() {
  //Serial.begin(9600); 
  int i; 
  randomSeed(analogRead(0));
  for (i=0;i<sizeof(pins);i=i+1){
    if (pins[i]==1){
      pinMode(i, OUTPUT);
      freq[i]=random(750,10000);
      stat[i]=random(0,freq[i]);
    }
  }
}

// the loop function runs over and over again forever
void loop() {
  long phase;
  int i;
  double fade;
  double grad;
  double pwm;
  double cycle;
  double state;
  
  tick=micros();
  for (i=0;i<sizeof(pins);i=i+1){
    if (pins[i]==1){
      phase=(tick+(stat[i]*1000)) % ((freq[i]*1000));
      
      grad = (double)phase / ((double)freq[i]*1000);
      fade= pow(grad,2);
      
      cycle = fade * 20000.0;
      state= phase % 20000;

      if (i==1){
        /*Serial.print(tick);      
        Serial.print(",");
        Serial.print(stat[i]);
        Serial.print(",");
        Serial.print(freq[i]);
        Serial.print(",");
        Serial.print(phase);
        Serial.print(",");
        Serial.print(grad);
        

        Serial.print(fade);
        Serial.print(",");
        Serial.print(cycle);
        Serial.print(",");
        Serial.print(state);
        
        Serial.println("");*/
      }
      
      
      if (state < cycle){
        digitalWrite(i,HIGH);
      }else{
        digitalWrite(i,LOW);
      }      
    } 
  }
}
