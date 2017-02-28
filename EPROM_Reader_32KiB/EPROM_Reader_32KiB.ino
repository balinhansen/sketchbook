// Made some ridiculous circuit to dump the firmware off some ancient 
// parallel 27C256 EPROM (UV-flashable) PROM chip I pulled off an ISA
// 14.4kbps modem using some 74HS595s and maybe a 74LS161. I have a 
// drawing of the PCB ... somewhere

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
