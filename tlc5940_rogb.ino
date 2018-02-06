
#include "Tlc5940.h"
int pixels=4;
int channelsperpixel=4;
int pixel,channel;

int modes=8;
int mode=8;
int color=0;
int neighbor=0;
int neighborgrey=0;
int delayspeed=66;



void setup()
{
  Tlc.init();
}

   int c;
   int count=0;
   
void loop()
{
  int r,o,g,b;
  int flash,rpixel;
   
  

  switch (mode){
   case 1:
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
    int greyscale=random(0,4095);
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
 break;

 case 2:
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
    for (int channel=0;channel < channelsperpixel;channel++){
      int greyscale=random(0,4095);
      c=pixel*channelsperpixel+channel;
     Tlc.set(c,greyscale);
      }
    }
  
      Tlc.update();
 break;
 
 
 case 3:
   r=random(0,4095);
   o=random(0,4095);
   g=random(0,4095);
   b=random(0,4095);
   
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     int greyscale=random(0,4095);
     
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
      switch(channel%channelsperpixel){
        case 0:
        color=r;
        break;
        case 1:
        color=o;
        break;
        case 2:
        color=g;
        break;
        case 3:
        color=b;
      }
     Tlc.set(c,color);
      }
    }
      Tlc.update();
  break;
  
  
  
  case 4:
   color=random(0,4);
   if (random(0,1)==1){
     neighbor=color+1;
   }else{
     neighbor=color-1;
   }
   
   if (neighbor>channelsperpixel-1){neighbor=0;}
   if (neighbor<0){neighbor=channelsperpixel-1;}
   
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
   int greyscale=0;
   
      if (c%channelsperpixel == color){
        greyscale=4095;
      }
      
      if (c%channelsperpixel == neighbor){
        greyscale=random(0,4095);
      }
      
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
  break;
  
  
  
  case 5:
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     
   color=random(0,4);
   if (random(1)==1){
     neighbor=color+1;
   }else{
     neighbor=color-1;
   }
   
   if (neighbor>channelsperpixel-1){neighbor=0;}
   if (neighbor<0){neighbor=channelsperpixel-1;}
   
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
   int greyscale=0;
   
      if (c%channelsperpixel == color){
        greyscale=4095;
      }
      
      if (c%channelsperpixel == neighbor){
        greyscale=random(0,4095);
      }
      
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
  break;
  
  
  
  case 6:
   flash=random(1,1);
   rpixel=random(0,channelsperpixel);
   
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     
   color=random(0,4);
   if (random(0,1)==1){
     neighbor=color+1;
   }else{
     neighbor=color-1;
   }
   
   if (neighbor>channelsperpixel-1){neighbor=0;}
   if (neighbor<0){neighbor=channelsperpixel-1;}
   
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
   int greyscale=0;
   
      if (c%channelsperpixel == color && flash==1 && rpixel==pixel){
        greyscale=4095;
      }
      
      if (c%channelsperpixel == neighbor && flash==1 && rpixel==pixel){
        greyscale=random(0,4095);
      }
      
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
  break;
  
  
  
  
  case 7:
  
     if (count%int(NUM_TLCS*16/channelsperpixel)==0){
       
   color=random(0,4);
   if (random(0,1)==1){
     neighbor=color+1;
   }else{
     neighbor=color-1;
   }
   
   if (neighbor>channelsperpixel-1){neighbor=0;}
   if (neighbor<0){neighbor=channelsperpixel-1;}
   
        neighborgrey=random(0,4095);
     }
     
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     
     
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
   int greyscale=0;
   
      if (c%channelsperpixel == color && count%int(NUM_TLCS*16/channelsperpixel)==pixel){
        greyscale=4095;
      }
      
      if (c%channelsperpixel == neighbor && count%int(NUM_TLCS*16/channelsperpixel)==pixel){
        greyscale=neighborgrey;
      }
      
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
  break;
  
  
  case 8:
  
   for (int pixel = 0; pixel < floor(NUM_TLCS*16 / channelsperpixel); pixel++) {
     
   color=random(0,4);
   if (random(0,1)==1){
     neighbor=color+1;
   }else{
     neighbor=color-1;
   }
   
   if (neighbor>channelsperpixel-1){neighbor=0;}
   if (neighbor<0){neighbor=channelsperpixel-1;}
   
        neighborgrey=random(0,4095);
     
     
    for (int channel=0;channel < channelsperpixel;channel++){
      c=pixel*channelsperpixel+channel;
      
   int greyscale=0;
   
      if (c%channelsperpixel == color && count%int(NUM_TLCS*16/channelsperpixel)==pixel){
        greyscale=4095;
      }
      
      if (c%channelsperpixel == neighbor && count%int(NUM_TLCS*16/channelsperpixel)==pixel){
        greyscale=neighborgrey;
      }
      
     Tlc.set(c,greyscale);
      }
    }
      Tlc.update();
  break;
  
  
  
  }
  
  switch (mode){
    case 1:
      delay(delayspeed);
      break;
 case 2:
      delay(delayspeed);
      break;
 case 3:
      delay(delayspeed);
      break;
 case 4:
      delay(delayspeed);
      break;
 case 5:
      delay(delayspeed);
      break;
 case 6:
      delay(delayspeed);
      break;
 case 7:
      delay(delayspeed);
      break;
 case 8:
      delay(delayspeed);
      break;
  }
  
  
  if (count > 200){
    count=0;
    mode++;
    if (mode > modes){
    mode=random(1,modes);
    }
    
  }else{
    count++;
  }

}

