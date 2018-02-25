#include "NewPing.h"
#include "Tlc5940.h"
#include "tlc_servos.h"

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


int motormodes=18;
int motormode=1;
int delayspeed=10;

   int c;
   int motorcount=0;
   int motorcounts=100;
   
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

void loop()
{
  
unsigned int uS;

  if (motorcount > motorcounts){
    motorcount=0;
    motormode++;
    if (motormode > motormodes){
    motormode=1;//round(random(1,modes+1)); //mode=1;//
    //Serial.println(random(1,3));
    }
  }
  
  if (motorcount == 0 && (motormode == 0 || motormode == 1 || motormode == 3 || motormode == 5 || motormode == 7 || motormode == 9 || motormode == 11 || motormode == 13 || motormode == 15 || motormode == 17)){
    uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    pingDistance = uS / US_ROUNDTRIP_CM;
    //Serial.print(pingDistance);
    //Serial.println(" cm");
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

