#include </home/balin/sketchbook/libraries/MIDI/src/MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();


#define TONE 11
#define LED_R 5
#define LED_G 6
#define LED_B 7


void LightNote (int midinote){
  
  switch (midinote){
    case 48: // tom 1
    
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_G,HIGH);
      delay(100);
      digitalWrite(LED_R,LOW);
      digitalWrite(LED_G,LOW);
    break;
    
    case 36: // kick
    
      digitalWrite(LED_R,HIGH);
      delay(100);
      digitalWrite(LED_R,LOW);
    break;
    
  
    case 45: // tom 2
    
      digitalWrite(LED_G,HIGH);
      digitalWrite(LED_B,HIGH);
      delay(100);
      digitalWrite(LED_G,LOW);
      digitalWrite(LED_B,LOW);
    break;

    case 38: // snare
    
      digitalWrite(LED_G,HIGH);
      delay(100);
      digitalWrite(LED_G,LOW);
    break;
 
 
    case 41: // tom 3
    
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_B,HIGH);
      delay(100);
      digitalWrite(LED_R,LOW);
      digitalWrite(LED_B,LOW);
    break;

    case 42: // closed hat
    
      digitalWrite(LED_R,HIGH);
      delay(50);
      digitalWrite(LED_R,LOW);
    break;
  
  
    case 51: // ride
    
      digitalWrite(LED_G,HIGH);
      delay(50);
      digitalWrite(LED_G,LOW);
    break;

    case 46: // open hat
    
      digitalWrite(LED_B,HIGH);
      delay(50);
      digitalWrite(LED_B,LOW);
    break;


    case 49: // crash
    
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_G,HIGH);
      digitalWrite(LED_B,HIGH);
      delay(100);
      digitalWrite(LED_R,LOW);
      digitalWrite(LED_G,LOW);
      digitalWrite(LED_B,LOW);
    break;
  
    case 39: // claps
    
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_G,HIGH);
      digitalWrite(LED_B,HIGH);
      delay(10);
      digitalWrite(LED_R,LOW);
      digitalWrite(LED_G,LOW);
      digitalWrite(LED_B,LOW);
    break;


    case 65: // perc 1
    
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_G,HIGH);
      delay(50);
      digitalWrite(LED_R,LOW);
      digitalWrite(LED_G,LOW);
    break;
  
    case 67: // perc 2
      digitalWrite(LED_G,HIGH);
      delay(50);
      digitalWrite(LED_G,LOW);
    break;
    
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
    
    MIDI.begin();           // Launch MIDI, by default listening to channel 1.
}

void loop()
{
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
