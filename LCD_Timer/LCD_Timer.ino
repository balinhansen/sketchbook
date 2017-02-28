// This might be an earlier version of LCD_Effects, it's probably 
// garbage ...

#include <LiquidCrystal.h>
#include <LCDKeypad.h>;

long start=micros();

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // OSEPP

// make barchart custom characters:
byte b0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte b1[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte b2[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
byte b3[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};
byte b4[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};
byte b5[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte b6[8] = {
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111
};
byte b7[8] = {
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111
};
byte b8[8] = {
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011
};
byte b9[8] = {
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};

void setup() {
  // create a new character
  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  LoadChar(0,0);
  //Serial.begin(115200);

}

void loop() {
  WaitForUp();
  CountOff();
}


void WaitForUp(){
  lcd.setCursor(0,0);
  start=micros();
  
  while (micros() > start+3000000){
    lcd.print("Starting Countdown");
    waitButton();  
    waitReleaseButton(); 
  }
}

int waitButton()
{
  long beg=micros();
  int buttonPressed; 
  waitReleaseButton;
  lcd.blink();
  int blinks=2;
  int duration=10000000;
  while((buttonPressed=lcd.button())==KEYPAD_NONE || micros() < beg-(duration/(blinks*2))
  {
    if (   floor(  (micros()-beg) / ( duration/(blinks * 2) )  )  % 2 ){
      for (i=0;i<2;i++){
        for (j=0;j<16;j++){
          LoadChar(1,0);
          lcd.setCursor(j,i);
          lcd.write(1);
        }
      } 
    }
    setCursor(0,0);
  }
  return buttonPressed;
}

void waitReleaseButton()
{
  delay(50);
  while(lcd.button()!=KEYPAD_NONE)
  {
  }
  delay(50);
}


void CountOff() {
  int i, j, c;
  long last,k;
  static int t;
    k=((micros()-start)%20000000)/1000000;
    
    lcd.setCursor(0, 0);
    lcd.print("Hello World  "); 

    if (k<10){
      LoadChar(0,0);
      lcd.setCursor(14,0);
      lcd.write(byte(0));
      lcd.setCursor(15, 0);
    }else{
      if (k<100){
        lcd.setCursor(14,0);
      }
    }
    
    lcd.print(k); 
    last=micros();
    
    for (j=0;j<20;j++){
      c=j%10;
      LoadChar(1,c);
      lcd.setCursor(0,0);
      
      for (i=0;i<16;i++){
        lcd.setCursor(i,1);
        lcd.write(byte(1));
      }
      while (micros() < last+50000){
      
      }
      last=micros();
    }
}


void LoadChar(int t, int c){
    if (c==0){
      lcd.createChar(t, b0);
    }
    if (c==1){
      lcd.createChar(t, b1);
    }
    if (c==2){
      lcd.createChar(t, b2);
    }
    if (c==3){
      lcd.createChar(t, b3);
    }
    if (c==4){
      lcd.createChar(t, b4);
    }
    if (c==5){
      lcd.createChar(t, b5);
    }
    if (c==6){
      lcd.createChar(t, b6);
    }
    if (c==7){
      lcd.createChar(t, b7);
    }
    if (c==8){
      lcd.createChar(t, b8);
    }
    if (c==9){
      lcd.createChar(t, b9);
    }
}

/*
// last shown barchart value
int BarLastBlocks = 0;
const int ScrollTextLength = 11;
String ScrollTextField[ScrollTextLength] = {
  "                ",
  "Scroll Text Demo",
  "                ",
  "egg             ",
  "   egg          ",
  "     egg        ",
  "      egg       ",
  "      egg       ",
  "    splash      ",
  "----((..))------",
  "need new egg ;^)"};

void setup() {
  // create a new character
  lcd.createChar(1, b0);
  lcd.createChar(2, b1);
  lcd.createChar(3, b2);
  lcd.createChar(4, b3);  
  lcd.createChar(5, b4);
  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);

  Serial.begin(115200);

}

void loop() {
  int barDelay=20;
  // Print a message to the lcd.
  lcd.setCursor(0, 0);
  lcd.print("Barchart test  "); 
  // draw barchart
  // max barchart size = 16x5 = 80
  for (int j=0; j<1; j++){
    lcd.setCursor(15, 0);
    lcd.print(j); 
    for (int i=0; i<80; i++) {
      DrawBar(i);
      delay(barDelay);
    }
    for (int i=80; i>=0; i--) {
      DrawBar(i);
      delay(barDelay);
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Barchart reverse"); 
  // draw barchart
  // max barchart size = 16x5 = 80
  for (int j=0; j<1; j++){
    for (int i=0; i<80; i++) {
      DrawBarLeft(i);
      delay(barDelay);
    }
    for (int i=80; i>=0; i--) {
      DrawBarLeft(i);
      delay(barDelay);
    }
  }
  lcd.setCursor(0, 0);
  BarLastBlocks=0;
  lcd.print("Barchart random "); 
  for (int i=0; i<20; i++) {
    DrawBar(random(80));
    delay(100);
  }

  delay(1000); 
  ScrollText(1000);
  delay(2000);
}

void DrawBar(int value) {
  int fullblocks;
  int rightblock;
  int cursorPos;
  
  lcd.createChar(2, b1);
  lcd.createChar(3, b2);
  lcd.createChar(4, b3);  
  lcd.createChar(5, b4);

  lcd.setCursor(0, 1);

  // check value size and reset if neccessary
  if (value < 0) value = 0;
  if (value > 80) value = 80;
  // calulate number of full blocks
  fullblocks=0;
  while (fullblocks*5 < value) {
    fullblocks++;
  }
  fullblocks--;
  if (fullblocks < 0) fullblocks = 0;
  rightblock = value - fullblocks*5 + 1;
  cursorPos = fullblocks;
  if (BarLastBlocks < fullblocks) cursorPos = BarLastBlocks;
  lcd.setCursor(cursorPos, 1);
  for (int i=BarLastBlocks; i<fullblocks; i++) {
    lcd.write(6);
  }
  lcd.setCursor(fullblocks, 1);
  lcd.write(rightblock);
  for (int j=fullblocks+1; j<16; j++) {
    lcd.write(1);
  }
  BarLastBlocks = fullblocks;
}

void DrawBarLeft(int value) {
  int fullblocks;
  int rightblock;
  int cursorPos;
  
  lcd.createChar(2, b6);
  lcd.createChar(3, b7);
  lcd.createChar(4, b8);
  lcd.createChar(5, b9);

  lcd.setCursor(0, 1);

  value=80-value;
  // check value size and reset if neccessary
  if (value < 0) value = 0;
  if (value > 80) value = 80;
  // calulate number of full blocks
  fullblocks=0;
  while (fullblocks*5 < value) {
    fullblocks++;
  }
  fullblocks--;
  if (fullblocks < 0) fullblocks = 0;
  rightblock = value - fullblocks*5 + 1;
  cursorPos = fullblocks;
  if (BarLastBlocks < fullblocks) cursorPos = BarLastBlocks;
  lcd.setCursor(cursorPos, 1);
  for (int i=BarLastBlocks; i<fullblocks; i++) {
    lcd.write(1);
  }
  lcd.setCursor(fullblocks, 1);
  lcd.write(rightblock+5);
  for (int j=fullblocks+1; j<16; j++) {
    lcd.write(6);
  }
  BarLastBlocks = fullblocks;
}

void ScrollText (int sdelay) {
  String outp;
  int sline=0;
  for (int i=0; i<ScrollTextLength; i++) {
    sline=i;
    lcd.setCursor(0, 0);
    outp=ScrollTextField[sline];
    lcd.print(outp);
    sline=i+1;
    if (sline>=ScrollTextLength) sline = 0;
    lcd.setCursor(0, 1);
    outp=ScrollTextField[sline];
    lcd.print(outp);
    delay(sdelay);
  }
}


*/







