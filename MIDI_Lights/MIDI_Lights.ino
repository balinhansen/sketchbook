#include </home/balin/sketchbook/libraries/MIDI/src/MIDI.h>

#define TONE 11
#define LED_R 5
#define LED_G 6
#define LED_B 7

MIDI_CREATE_DEFAULT_INSTANCE();


double colors[12]={};
int pwm[3]={1023,1023,1023};
int debug=0;
int lighttest=0;
int n=0;




typedef struct color{
 float r;
 float g;
 float b;
};

color led={1,0,1};

color gradient[6]={
{1,0,0},
{1,1,0},
{0,1,0},
{0,1,1},
{0,0,1},
{1,0,1}
};

void LightNote (int midinote){
  
  double c;
  int stage;
  
  double phase;
  
  c=(double(midinote%12)/12)*(sizeof(gradient)/12);
  phase=c-floor(c);
  
  stage=floor(c);
  color a=gradient[stage];
  color b={};
  
  if (c>=(sizeof(gradient)/12)-1){
    b=gradient[0];
  }else{
    b=gradient[(int(floor(c))+1)];
  }
  
  //phase=random(0,10)/10;
  
  led.r=(a.r-((a.r-b.r)*phase));
  led.g=(a.g-((a.g-b.g)*phase));
  led.b=(a.b-((a.b-b.b)*phase));
   
  pwm[0]=1023-int(led.r*1023);
  pwm[1]=1023-int(led.g*1023);
  pwm[2]=1023-int(led.b*1023);
  
  if (debug){
    Serial.print(c);
    Serial.print(" ");
    Serial.println(phase);
    Serial.print(led.r);
    Serial.print(" ");
    Serial.print(led.g);
    Serial.print(" ");
    Serial.println(led.b);
  }
  
}


void LightOff(int midinote){
 // noTone(TONE);
}

// -----------------------------------------------------------------------------

void setup()
{
    pinMode(TONE, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,HIGH);
    digitalWrite(LED_B,HIGH);
    
    if (debug){ Serial.begin(115200); }
    
    
  if (lighttest){
    digitalWrite(LED_R,LOW);
     delay(500);
    digitalWrite(LED_R,HIGH);
     delay(100);
     digitalWrite(LED_G,LOW);
     delay(500);
    digitalWrite(LED_G,HIGH);
     delay(100);
     digitalWrite(LED_B,LOW);
     delay(500);
    digitalWrite(LED_B,HIGH);
     delay(2000);
  }
  
   // LightNote(60);
    
    
    if (!debug){ MIDI.begin();  }         // Launch MIDI, by default listening to channel 1.
}

void loop()
{
  
  
  if (debug || lighttest){
    if (n>100){n=0;}
    LightNote(n);
    n++;
    if (debug){delay(1000);}
  }
  
  
  
  unsigned long time=micros()&0x3ff;
  
  if (debug){ Serial.println(time); }
  
  if (debug){ delay(300); }
  
  if (time > pwm[0]){
    digitalWrite(LED_R,LOW);
  }else{
    digitalWrite(LED_R,HIGH);
  }
  
  if (time > pwm[1]){
    digitalWrite(LED_G,LOW);
  }else{
    digitalWrite(LED_G,HIGH);
  }
  
  if (time > pwm[2]){
    digitalWrite(LED_B,LOW);
  }else{
    digitalWrite(LED_B,HIGH);
  }
  
  
  
  if (!debug){
    
    if (MIDI.read())                // Is there a MIDI message incoming ?
    {
        switch(MIDI.getType())      // Get the type of the message we caught
        {
            case midi::NoteOn:       // If it is a Program Change,
                LightNote(MIDI.getData1());  // blink the LED a number of times
                                            // correponding to the program number
                                            // (0 to 127, it can last a while..)
                break;
            case midi::NoteOff:
                LightOff(MIDI.getData1());
                break;
            // See the online reference for other message types
            default:
                break;
        }
    }
   
  }
   
    
}
