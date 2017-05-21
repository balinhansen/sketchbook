
#include "Tlc5940.h"
int phases=4;
int phase=0;

void setup()
{
  Tlc.init();
}
   int maxed=4095;
   int brightness=0;
   int d_step=3;
   int direction=d_step;
   
void loop()
{
  int grayscale;
  int in,out;
  
  brightness+=direction;
  if (brightness>=maxed){
    brightness=0;
    phase++;
    if (phase>=phases){
      phase=0;
    }
  }
  
  if (phase<=0){
    out=phases-1;
  }else{
    out=phase-1;
  }
  
  if (phase+1>=phases){
    in=0;
  }else{
    in=phase+1;
  }
  
  int off=1;
  
  for (int channel = 0; channel < NUM_TLCS * 16; channel ++) {
    if (channel%phases==phase){
     Tlc.set(channel,maxed*pow(double(brightness)/maxed,3));
    }
  }
  /*
  for (int channel = 0; channel < NUM_TLCS * 16; channel ++) {
    if (channel%phases==phase){
     Tlc.set(channel,maxed);
    }
  }
  */
  
  for (int channel = 0; channel < NUM_TLCS * 16; channel ++) {
    if (channel%phases==out){
     Tlc.set(channel,maxed-maxed*pow(double(brightness)/maxed,3));
    }
  }
  
    
  
      Tlc.update();
  delayMicroseconds(100); 

}

