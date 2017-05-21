
#include "Tlc5940.h"

void setup()
{
  Tlc.init();
}

void loop()
{
  
  double centricity;
  int grayscale;
  
  int direction = 1;
  for (int channel = 0; channel < NUM_TLCS * 16; channel += direction) {
    centricity=abs(double(channel-NUM_TLCS*16/2)/double(NUM_TLCS*16/2));
    grayscale=int(4095*sin(pow((1.0-centricity),7)*90));
    
    Tlc.clear();

    if (channel == 0) {
      direction = 1;
    } else {
      Tlc.set(channel - 1, 1000*sin(pow((1.0-centricity),7)*90));
    }
    Tlc.set(channel, grayscale);
    if (channel != NUM_TLCS * 16 - 1) {
      Tlc.set(channel + 1, 1000*sin(pow((1.0-centricity),7)*90));
    } else {
      direction = -1;
    }

    Tlc.update();

    delay(75);
    
  }

}

