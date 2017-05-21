
#include "Tlc5940.h"

void setup()
{
  Tlc.init();
}
   
void loop()
{
  double gradient;
  int grayscale;
  
  for (int channel = 0; channel < NUM_TLCS * 16; channel ++) {
    gradient=channel/double(NUM_TLCS*16);
    grayscale=int(4095*pow(gradient,3));
    
    Tlc.set(channel, grayscale);

    Tlc.update();
    
  }

}

