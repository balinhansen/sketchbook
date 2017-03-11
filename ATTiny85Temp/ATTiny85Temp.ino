#include SoftwareSerial.h

const int Rx = 3;
const int Tx = 4;

SoftwareSerial mySerial(Rx,Tx);

const int counts=10;

int sensorPin = A2;
double temps[counts];
int count=0;
  
void setup(){
  //Serial.begin(115200);
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  mySerial.Begin(9600);
  analogReference(INTERNAL);
}

void loop(){
  int i;
  double celcius, fahrenheit, curtemp;
  double average,total=0;
  
  delay(100);
  
  curtemp=analogRead(sensorPin);
  
  delay (100);
  
  /*
  for (i=1;i<counts;i++){
    temps[i]=temps[i-1];
  }
  temps[0]=curtemp;
  
  count++;
  if (count > counts){count=counts;}
  
  for (i=0;i<count;i++){
    total+=temps[i];
  }
  
  average=total/count;
  */
  average=curtemp;
  
  celcius=average/9.31;
  
  fahrenheit=celcius*1.8+32;
  mySerial.print("Temperature: ");
  mySerial.print(celcius);
  mySerial.print("C / ");
  mySerial.print(fahrenheit);
  mySerial.println("F");
  
 
  delay(100);
 
}
