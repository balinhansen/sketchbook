#include </home/balin/sketchbook/libraries/MIDI/src/MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define TONE 11
#define LED 13                   // LED pin on Arduino Uno


double freq_from_midi(int midinote){
  int normalized_note;
  normalized_note = midinote-57;
  double twel=pow(2,float(1)/float(12));
  
  double freq = pow(twel,float(normalized_note))*220;
  return freq;
  
}

void SynthNote (int midinote){
  double freq;
  freq=freq_from_midi(midinote);
  tone(TONE,freq ,100);
}


void SynthOff(int midinote){
 // noTone(TONE);
}


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
