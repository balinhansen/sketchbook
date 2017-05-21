
#include "Tlc5940.h"

void setup()
{
  Tlc.init();
}
   int maxed=4095;
   int brightness=0;
   int d_step=80;
   int direction=d_step;
   
void loop()
{
  int grayscale;
  brightness+=direction;
  if (brightness>=maxed){brightness=maxed;direction=-1*d_step;}
  if (brightness<=0){brightness=0;direction=d_step;}
  
  for (int channel = 0; channel < NUM_TLCS * 16; channel ++) {
    
   Tlc.set(channel,maxed*pow(double(brightness)/maxed,3));

    Tlc.update();
    
  }
  delayMicroseconds(100); 

}

