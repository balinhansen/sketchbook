#include "NewPing.h"
#include "Tlc5940.h"
#include "tlc_servos.h"

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int mode=0; // 0 for off, 1 for data acquisition, 2 for motor ramping/braking, 3 for motor running

int motormodes=18;
int motormode=1;
int delayspeed=10;

   int c;
   int motorcount=0;
   int motorcounts=100;
   int startspeed=0;
   int fullspeed=4095;
   
   
   // Easter Egg
   int phases=4;
   int phase=0;
   int maxed=4095;
   int brightness=0;
   int d_step=1;
   int direction=d_step;
   
   
   
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int pingDistance = 0;

void setup()
{
  int i;
  
  //Serial.begin(115200);
  
//Tlc.init(0);  
  tlc_initServos(0); // Tunes TLC library to PWM frequencies
  
  for (i=0;i<16;i++){
     //tlc_setServo(i,0);
     Tlc.set(i,0);
  }
  Tlc.update();
}

void getDistance(){
  unsigned int uS;
  uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  pingDistance = uS / US_ROUNDTRIP_CM;
  //Serial.print(pingDistance);
  //Serial.println(" cm");
}

int motorTypes[19][4]={
  {0,0,0,0}, // Idle
  {1,0,1,0}, // Forward
  {-1,0,-1,0}, // Idle from Forward
  {1,1,1,1}, // Brake
  {-1,-1,-1,-1}, // Idle from Brake
  {0,1,0,1}, // Reverse
  {0,-1,0,-1}, // Idle from Reverse
  {1,0,0,0}, // Right
  {-1,0,0,0}, // Idle from Right
  {0,0,1,0}, // Left
  {0,0,-1,0}, // Idle from Left
  {0,1,0,0}, // Reverse Right
  {0,-1,0,0}, // Idle from Reverse Right
  {0,0,0,1}, // Reverse Left
  {0,0,0,-1}, // Idle from Reverse Left
  {1,0,0,1}, // Swivel Right
  {-1,0,0,-1}, // Idle from Swivel Right
  {0,1,1,0}, // Swivel Left
  {0,-1,-1,0} // Idle from Swivel Left
  
};

void motorRamping(){
  if (motorcount > motorcounts){
    motorcount=0;
    motormode++;
    if (motormode > motormodes){
    motormode=1;//round(random(1,modes+1)); //mode=1;//
    //Serial.println(random(1,3));
    }
  }
  
  switch (motormode){
    
   case 0: // Idle
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,0);
     Tlc.update();
   break;
  
  
   case 1: // Ramp to Forward
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
   break;
 
   case 2: // Idle from Forward
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
       
   case 3: // Ramp to Brake
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,double(motorcount)/motorcounts*4095);
     Tlc.set(1,double(motorcount)/motorcounts*4095);
     Tlc.set(2,double(motorcount)/motorcounts*4095);
     Tlc.set(3,double(motorcount)/motorcounts*4095);
     Tlc.set(4,double(motorcount)/motorcounts*4095);
     Tlc.set(5,double(motorcount)/motorcounts*4095);
     Tlc.set(6,double(motorcount)/motorcounts*4095);
     Tlc.set(7,double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
 
       
   case 4: // Idle from Brake
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(1,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(2,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(3,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(4,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(5,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(6,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(7,4095-double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
 
   case 5: // Ramp to Reverse
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,double(motorcount)/motorcounts*4095);
     Tlc.set(2,0);
     Tlc.set(3,double(motorcount)/motorcounts*4095);
     Tlc.set(4,0);
     Tlc.set(5,double(motorcount)/motorcounts*4095);
     Tlc.set(6,0);
     Tlc.set(7,double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
 
   case 6: // Idle From Reverse
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(2,0);
     Tlc.set(3,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(4,0);
     Tlc.set(5,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(6,0);
     Tlc.set(7,4095-double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
 
    
   case 7: //Ramp Up to Turn Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,0);
     Tlc.set(4,double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
   case 8: // Idle from Turning Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,0);
     Tlc.set(4,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
   
   case 9: //Ramp Up to Turn Left
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,0);
     Tlc.set(2,double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,0);
     Tlc.set(6,double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
   case 10: // Idle from Turning Left
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,0);
     Tlc.set(2,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,0);
     Tlc.set(6,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
   case 11: //Ramp Up to Turn Reverse Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,double(motorcount)/motorcounts*4095);
     Tlc.set(2,0);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,double(motorcount)/motorcounts*4095);
     Tlc.set(6,0);
     Tlc.set(7,0);
     Tlc.update();
   break;
  
   case 12: // Idle from Turning Reverse Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(2,0);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(6,0);
     Tlc.set(7,0);
     Tlc.update();
   break;
   
   case 13: //Ramp Up to Turn Reverse Left
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,double(motorcount)/motorcounts*4095);
     Tlc.set(4,0);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
  
   case 14: // Stop from Turning Reverse Left
     //tlc_setServo(0,double(count)/*180);
     Tlc.set(0,0);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(4,0);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,4095-double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
   
   case 15: // Ramp Up to Swivel Left
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,double(motorcount)/motorcounts*4095);
     Tlc.set(2,double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,double(motorcount)/motorcounts*4095);
     Tlc.set(6,double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
 break;
 
    case 16: // Stop from Swivel Left
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,0);
     Tlc.set(1,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(2,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(3,0);
     Tlc.set(4,0);
     Tlc.set(5,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(6,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(7,0);
     Tlc.update();
  break;
 
  case 17: // Ramp Up to Swivel Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,double(motorcount)/motorcounts*4095);
     Tlc.set(4,double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
   
   case 18: // Stop from Swivel Right
     //tlc_setServo(0,double(count)/10*180);
     Tlc.set(0,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(1,0);
     Tlc.set(2,0);
     Tlc.set(3,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(4,4095-double(motorcount)/motorcounts*4095);
     Tlc.set(5,0);
     Tlc.set(6,0);
     Tlc.set(7,4095-double(motorcount)/motorcounts*4095);
     Tlc.update();
   break;
 
  }
  
  switch (motormode){
    case 0:
      delay(delayspeed);
      break;
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
    case 9:
      delay(delayspeed);
      break;
    case 10:
      delay(delayspeed);
      break;
    case 11:
      delay(delayspeed);
      break;
    case 12:
      delay(delayspeed);
      break;
    case 13:
      delay(delayspeed);
      break;
    case 14:
      delay(delayspeed);
      break;
    case 15:
      delay(delayspeed);
      break;
    case 16:
      delay(delayspeed);
      break;
    case 17:
      delay(delayspeed);
      break;
    case 18:
      delay(delayspeed);
      break;
  }
  motorcount++;
}

void newmotorRamp(){
  
}

void motorRun(){
  for (int i=0;i<4;i++){
    switch (motorTypes[motormode][i]){
      case 0:
      Tlc.set(i,fullspeed);
      break;
      case 1:
        Tlc.set(i,fullspeed);
        break;
      case -1:
        Tlc.set(i,0);
        break;
    }
  }
  Tlc.update();
  delay(100);
}



void data(){
  
}



// Easter Egg/Idle Function(s)

void idle(){
  
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
      delay(73);
}




void loop()
{
  switch (mode){
    case 0:
    idle();
    break;
    
    case 1:
    data();
    break;
    
    case 2:
    motorRamping();
    break;
    
    case 3:
    motorRun();
    break;
  }
}

