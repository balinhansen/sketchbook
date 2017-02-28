int addr_latch=10;
int addr_clk=11;
int addr_data=12;
int data_latch=9;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(addr_latch, OUTPUT);
  pinMode(addr_clk, OUTPUT);
  pinMode(addr_data, OUTPUT);
  pinMode(data_latch, OUTPUT);
  digitalWrite(addr_latch,LOW);
  digitalWrite(data_latch,HIGH);
}

// the loop function runs over and over again forever
void loop() {
 shiftOut(addr_data,addr_clk,LSBFIRST,0xb4);
 digitalWrite(addr_latch,HIGH);
 digitalWrite(addr_latch,LOW);
 delay(1000);              // wait for a second
}
