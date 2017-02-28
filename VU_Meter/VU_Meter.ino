// This sketch utilitized my 74F595 shift-register driven 
// LED light bar emulate VU Meter light peaks and such. 
// I don't believe it can actually read an analogue signal 
// and display the volume, wouldn't that be great?


int clockpin=4;
int latchpin=5;
int datapin=6;
int peak;
//unsigned long peaktime=0;
int count=0;

void setup(){
  
  Serial.begin(115200);
  pinMode(clockpin,OUTPUT);
  pinMode(latchpin,OUTPUT);
  pinMode(datapin,OUTPUT);
  
 digitalWrite(clockpin,LOW);
 digitalWrite(latchpin,LOW);
 digitalWrite(datapin,LOW);
 
}

void loop(){
 int cur;
 byte output=0x00;
 int data;
 int i;
 int vol;
 
 vol=random(0,8);
 
 /*if (micros() > peaktime+1000000){
   peak=vol;
 }*/
 
 if (count>4){
   peak=vol;
   count=0;
 }
 
 if (vol >= peak){
   peak=vol;
//   peaktime=micros();
   count=0;
 }
 
 count++;
 
 for (i=0;i<vol;i++){
   output=1<<i|output;
 }
 
 output=1<<peak|output;
 digitalWrite(clockpin,HIGH);
 digitalWrite(clockpin,LOW);
 
 digitalWrite(clockpin,HIGH);
 digitalWrite(clockpin,LOW);

 for (i=0;i<8;i++){
   data=output&(1<<i);  
   if (data){
     digitalWrite(datapin,HIGH);
   }else{
     digitalWrite(datapin,LOW);
   }
   digitalWrite(clockpin,LOW);
   digitalWrite(clockpin,HIGH);
   digitalWrite(datapin,LOW);
 }
 
 digitalWrite(clockpin,LOW);
 digitalWrite(latchpin,HIGH);
 digitalWrite(clockpin,HIGH);
 digitalWrite(latchpin,LOW);

// delay(100);

 Serial.println(output);
}
