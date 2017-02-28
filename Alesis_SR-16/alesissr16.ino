#include </home/balin/sketchbook/libraries/MIDI/src/MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This example shows the old way of checking for input messages.
// It's simpler to use the callbacks now, check out the dedicated example.

#define TONE 11
#define LED 13                   // LED pin on Arduino Uno

// -----------------------------------------------------------------------------

void BlinkLed(byte num)         // Basic blink function
{
  num=0;
    for (byte i=0;i<num;i++)
    {
        digitalWrite(LED,HIGH);
        delay(50);
        digitalWrite(LED,LOW);
        //delay(450);
    }
}

double freq_from_midi(int midinote){
  int normalized_note;
  normalized_note = midinote-57;
  double twel=pow(2,float(1)/float(12));
  
  double freq = pow(twel,float(normalized_note))*220;
  return freq;
  
}

void SynthNote (int midinote){
  int normalized_note;
  double freq;
  int blink_note=0;
  
  switch (midinote){
    case 48: // tom 1
    Thump();
    break;
    
    case 36: // kick
    Stick();
    Thump();
    break;
    
  
    case 45: // tom 2
    Stick();
    break;

    case 38: // snare
    Stick();
    Whomp();
    break;
 
 
    case 41: // tom 3
    Squeek();
    break;

    case 42: // closed hat
    Stick();
    Whomp();
    Squeek();
    break;
  
  
    case 51: // ride
    Sticks();
    break;

    case 46: // open hat
    Noise(100000, 4000,6000);
    break;


    case 49: // crash
    Noise(10000, 100,1000);
    break;
  
    case 39: // claps
    Noise(100000, 3000,5000);
    break;


    case 65: // perc 1
    Whomp();
    break;
  
    case 67: // perc 2
    Noise(100000, 2000,4000);
    break;
    
  }
  
  freq=freq_from_midi(midinote);
  
  if (blink_note){
     tone(TONE,freq ,100);
     BlinkLed(1);
  }
  
  
  //BlinkLed(int(abs(midinote%10)));
}


void SynthOff(int midinote){
 // noTone(TONE);
}


void Noise(unsigned long dur,int minr, int maxr){
  unsigned long elap=0;
  int tog=1;
  int peak;
  
  while (elap<dur){
    peak=random(minr, maxr);
    elap+=peak;
    delayMicroseconds(peak);
    if (tog){
      digitalWrite(TONE,HIGH);
      tog=0;
    }else{
      digitalWrite(TONE,LOW);
      tog=1; 
    }
  } 
}

void Sticks(){
  int i;
  for (i=0;i<5;i++){
    Stick();
    delay(random(0,10));
  }
}

void Stick(){
  unsigned long dur=100000;
  unsigned long elap=0;
  int i;
  
  while (elap<dur){
    elap+=100/i;
    Noise(dur/100,100,100*i);
    i++;
  }
}

void Thump(){
  unsigned long dur=100000;
  unsigned long elap=0;
  int i;
  
  while (elap<dur){
    elap+=100*i;
    Noise(100*i,100,100*i);
    i++;
  }
}

void Squeek(){
  unsigned long dur=100000;
  unsigned long elap=0;
  int i=1;
  
  while (i<10){
    elap+=1000*(10-i);
    Noise(1000*(10-i),100,1000*(10-i));
    i++;
  }
}

void Whomp(){
  unsigned long dur=100000;
  unsigned long elap=0;
  int i;
  
  while (elap<dur){
    elap+=1000*i;
    Noise(1000*i,100,1000*i);
    i++;
  }
}

// -----------------------------------------------------------------------------

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TONE, OUTPUT);
    
    MIDI.begin();           // Launch MIDI, by default listening to channel 1.
}

void loop()
{
    if (MIDI.read())                // Is there a MIDI message incoming ?
    {
        switch(MIDI.getType())      // Get the type of the message we caught
        {
            case midi::NoteOn:       // If it is a Program Change,
                SynthNote(MIDI.getData1());  // blink the LED a number of times
                                            // correponding to the program number
                                            // (0 to 127, it can last a while..)
                break;
            case midi::NoteOff:
                SynthOff(MIDI.getData1());
                break;
            // See the online reference for other message types
            default:
                break;
        }
    }
}
