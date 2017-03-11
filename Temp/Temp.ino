const int counts=10;

int sensorPin = A0;
double temps[counts];
int count=0;
  
void setup(){
  Serial.begin(115200);
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
  Serial.print("Temperature: ");
  Serial.print(celcius);
  Serial.print("C / ");
  Serial.print(fahrenheit);
  Serial.println("F");
  
 
  delay(100);
 
}
