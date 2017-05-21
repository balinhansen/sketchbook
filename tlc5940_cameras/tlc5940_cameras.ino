
#include "Tlc5940.h"

void setup()
{
  Tlc.init();
}
   
   int fades[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   int speeds[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   int ticks=0;
   
void loop()
{
  int i,hit;
  
  while (1){
   Tlc.clear();
   
   if (ticks <=0){
    hit=random(16);
    fades[hit]=4095;
    speeds[hit]=random(64,320);
    
    ticks=random(75);
   }
   
    for (i=0;i<16;i++){
      Tlc.set(i, fades[i]);
      if (fades[i]>=speeds[i]){
        fades[i]+=-speeds[i];
      }else{
        fades[i]=0;
      }
    }
    
       
    Tlc.update();
    delay(5);
    ticks+=-1;
    
  }
    
}

