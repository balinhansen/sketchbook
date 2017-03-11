int red=0;
int yellow=1;
int green=3;
int blue=4;

int oldlit=-1;

const int counts=10;

int sensorPin = A1;
double temps[counts];
int count=0;
  
void setup(){
  analogReference(INTERNAL);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT); 
}

void loop(){
  int i;
  double celcius, fahrenheit, curtemp;
  double average,total=0;
  int lit=-1;
  
  delay(100);
  
  curtemp=analogRead(sensorPin);
  
  delay (100);

  average=curtemp;
  
  celcius=average/9.31;
  
  fahrenheit=celcius*1.8+32;

  if (fahrenheit < 65){
    lit='blue';
  }
  if (fahrenheit >=65 && fahrenheit < 75){
    lit='green';
  }
  if (fahrenheit >=75 && fahrenheit < 85){
    lit='yellow';
  }
  if (fahrenheit >= 85){
    lit='red';
  }
  
  if (oldlit != lit){     
    switch (oldlit){
      case 'red':
      digitalWrite(red,LOW);
      break;
      case 'yellow':
      digitalWrite(yellow,LOW);
      break;
      case 'green':
      digitalWrite(green,LOW);
      break;
      case 'blue':
      digitalWrite(blue,LOW);
      break;
    }  
    oldlit=lit;
  }
  
  switch (lit){
    case 'red':
    digitalWrite(red,HIGH);
    break;
    case 'yellow':
    digitalWrite(yellow,HIGH);
    break;
    case 'green':
    digitalWrite(green,HIGH);
    break;
    case 'blue':
    digitalWrite(blue,HIGH);
    break;
  }  
  
  delay(100);
 
}
