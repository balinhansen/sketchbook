#include <dht.h>

dht DHTA;
dht DHTB;
dht DHTC;

#define DHT11_PINA A1

#define DHT11_PINB A4
#define DHT11_PINC A5



void setup(){
  Serial.begin(9600);
  
  delay(100);                   // Wait to synchronize 
}

void loop(){

  int chk = DHTA.read11(DHT11_PINA);
  Serial.println("Sensor 1: ");
  
  Serial.print(DHTA.temperature);
  Serial.print((char)176);
  Serial.print("C ");
  Serial.print(DHTA.humidity);
  Serial.println("%");
  Serial.println("");
  

  chk = DHTB.read11(DHT11_PINB);
  
  Serial.println("Sensor 2: ");
  Serial.print(DHTB.temperature);
  Serial.print((char)176);
  Serial.print("C ");
  Serial.print(DHTB.humidity);
  Serial.println("%");
  Serial.println("");
  

  chk = DHTC.read11(DHT11_PINC);
  
  Serial.println("Sensor 3: ");
  Serial.print(DHTC.temperature);
  Serial.print((char)176);
  Serial.print("C ");
  Serial.print(DHTC.humidity);
  Serial.println("%");
  Serial.println("");
  

  delay(1000);                   // Short delay between reads
}

