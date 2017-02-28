// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include "NewPing.h"
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SHIFT_SPEED  33  // The delay between RGB LED shift points in ms.
#define redPin       6
#define bluPin     3
#define grnPin      5
#define DEBUG      1 // DEBUG counter; if set to 1, will write values back via serial

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int pingDistance = 0;
unsigned int flashCounter = 0;
boolean ledStatus = false;

int gradient[10][3]={
  {0,0,0},
  {255,255,255},
  {255,0,0},
  {255,255,0},
  {0,255,0},
  {0,255,255},
  {0,0,255},
  {255,0,255},
  {255,255,255},
  {0,0,0}
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(grnPin, HIGH);
  digitalWrite(bluPin, HIGH);
  digitalWrite(redPin, HIGH);
}

int count=0;

void loop() {            
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  pingDistance = uS / US_ROUNDTRIP_CM;

 
  if(pingDistance > MAX_DISTANCE)
      pingDistance = MAX_DISTANCE;

  float color=(float(pingDistance) / float(MAX_DISTANCE))*((float(sizeof(gradient))/6.0f)-1.0f);
  float fade=color-float(int(color));
  
 int set=int(color);
 float redVal, grnVal, bluVal;
 redVal=float(gradient[set][0])-(float(gradient[set][0])-float(gradient[set+1][0]))*fade;
 grnVal=float(gradient[set][1])-(float(gradient[set][1])-float(gradient[set+1][1]))*fade;
 bluVal=float(gradient[set][2])-(float(gradient[set][2])-float(gradient[set+1][2]))*fade;
 int r,g,b;
 r=int(redVal);
 g=int(grnVal);
 b=int(bluVal);
 count++;
  // Convert to 0-255
  
// if ((count % 10)==0){
   Serial.print("color: ");
   Serial.print(color,DEC);
   Serial.print(" set: ");
   Serial.print(int(color),DEC);
   Serial.print(" fade: ");
   Serial.print(int(fade));
   Serial.print(" R: ");
   Serial.print(r);
   Serial.print(" G: ");
   Serial.print(g);
   Serial.print(" B: ");
   Serial.println(b);
//   count=0;

// */
  if (pingDistance !=0){
    analogWrite(redPin, r);   // Write current values to LED pins
    analogWrite(grnPin, g);      
    analogWrite(bluPin, b); 
  }
}

