// This looks to be a copy of LCD_Effects ... I have no idea 
// which is the superior version ...

#include <LiquidCrystal.h>
#include <LCDKeypad.h>;

long start=micros();
int state=0,nstate;
int count=0;
int rel=0;

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // OSEPP
LCDKeypad lcd;

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
  lcd.noCursor();
  LoadChar(0,0);
  lcd.setCursor(0,0);
  
  //Serial.begin(115200);

}

void loop() {
  
  if (state == 0){
    AutoStart();
  }
  if (state == 1){
    CountOff();
  }
  if (state == 2){
    Alarm();
  }
  
  if (state == 3){
    PresstoStart();
  }
  
  if (state == 4){
    ShowCounts();
  }
  
  if (state == 5){
    StartRelease();
  }
    
}

void PresstoStart(){
  long phase;
  int stat, buttonPressed;
  static int pstat, sent;
  
  long duration=1000000,blinks=1;
  
  if ((buttonPressed=lcd.button()) ==KEYPAD_NONE){

    phase=((micros()-start) % duration);
    
    stat=int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )))  & 1;
    
    if (pstat != stat){
      sent=1;
      if (stat){
        lcd.setCursor(0,0);
        lcd.print(" Press to Start");
        lcd.setCursor(0,1);
        lcd.print(" When Lungs Full");
      }else{
        LineSet(0,0,0);
        LineSet(1,0,0); 
      }
      pstat=stat;
    }   
  }else{
    sent=0;
    nstate=1;
    StartRelease();
  }
}

void StartRelease(){
  if (lcd.button()!=KEYPAD_NONE)
  { 
    state=5;
    LineBlink(0,1000000,4,start);
    LineBlink(1,1000000,4,start);
    rel=1;
  }else{
    if (rel==1){
      state = nstate;
      start=micros();
      rel=0;
    }
  }
}

void Alarm(){
  long phase,duration=1000000,blinks=4;
  int stat;
  static int pstat,sent;
  
  if (lcd.button()==KEYPAD_NONE && micros() < start+25000000){
    phase=((micros()-start) % duration);
    stat=int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )))  & 1;
    if (stat != pstat){
      if (!sent){
        sent=1;
        LineSet(0,0,0);
        lcd.setCursor(0,0); 
        lcd.print("     Exhale!");
      }
      pstat=stat;  
      if (stat){  
        LineSet(1,0,0);
      }else{
        LineSet(1,1,5);
      }
    }
  }else{
    sent=0;
    pstat=-1;
    if (lcd.button()!=KEYPAD_NONE){
      nstate=3;
      StartRelease();
    }else{
      state=4;
    }
  }
}

void ShowCounts(){
  long phase,duration=1000000,blinks=2;
  int stat;
  static int pstat,sent;
  
  if (lcd.button()==KEYPAD_NONE && micros() < start+30000000){
    phase=((micros()-start) % duration);
    stat=int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )))  & 1;
    if (stat != pstat){
      if (!sent){
        sent=1;
        LineSet(0,0,0);
        lcd.setCursor(0,0); 
        lcd.print("You Have Taken");
      }
      pstat=stat;  
      if (stat){  
        LineSet(1,0,0);
        lcd.setCursor(0,1);
        lcd.print("   ");
        lcd.print(count);
        if (count == 1){
          lcd.print(" Hit!");
        }else{
          lcd.print(" Hits!");
        }
      }else{
        LineSet(1,1,5);
      }
    }
  }else{
    sent=0;
    pstat=-1;
    if (lcd.button()!=KEYPAD_NONE){
      nstate=3;
      StartRelease();
    }else{
      state=3;
    }
  }
}

void LineSet(int l, int c, int s){
  int i;
  LoadChar(c,s);
  for (i=0;i<16;i++){
    lcd.setCursor(i,l);
    lcd.write(byte(c));
  } 
}

void LineBlink(int r, long duration, long blinks, long beg){
  long phase;
  int stat;
  phase=((micros()-beg) % duration);
  stat=int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )))  & 1;
  
  if (stat){
    LineSet(r,1,5);
  }else{
    LineSet(r,0,0);
  }
}

void AutoStart()
{
  long phase;
  int buttonPressed; 
  
  long blinks=2;
  int i,j,stat;
  long duration=1000000;
  static int pstat,sent;
  
  if (((buttonPressed=lcd.button()) ==KEYPAD_NONE) && state==0 && micros() < start+5000000 )
  {   
    
    phase=((micros()-start) % duration);
    stat=int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )))  & 1;
  
    if (pstat != stat){
      pstat=stat;
    
      if (stat){
        if (!sent){
          sent=1;
          LineSet(0,0,0);
          LineSet(1,0,0);
          lcd.setCursor(0,0);
          lcd.print(" Auto-Starting");
          lcd.setCursor(0,1);
          lcd.print("  Hit Counter");
        }else{
          lcd.setCursor(0,1);
          lcd.print("  Hit Counter");
        }
      }else{
        lcd.setCursor(0,1);
        LineSet(1,0,0);
      }
      
    }
    
  }else{
    sent=0;
    pstat=-1;
    state=1;
    if (lcd.button()!=KEYPAD_NONE){
      nstate=3;
      StartRelease();
    }
  }
}

void CountOff() {
  int i, j, c;
  long k,phase,duration=1000000,blinks=10;
  int stat;
  static int fade, sent;
  
  if (lcd.button()==KEYPAD_NONE){
    k=((micros()-start)%20000000)/1000000;
 
    if (!sent){
      sent=1;
      LineSet(0,0,0);
      lcd.setCursor(0,0);
      lcd.print("Hold That Rip"); 
    }
    
    if (micros() > start+20000000){
      state=2;
      k=20;
      sent=0;
      fade=-1;
      count=count+1;
    }
    
    phase=((micros()-start) % duration);
    stat = int(floor(  double(phase) / double(( double(duration)/double(blinks * 2) )  )));
  
    if (stat != fade){
      fade=stat;
      
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
      j=floor(double(micros()-start) / double(1000000/20));
    
      c=j%10;
      LoadChar(1,c);
      for (i=0;i<16;i++){
        lcd.setCursor(i,1);
        lcd.write(byte(1));
      }
    }
  }else{
    sent=0;
    fade=-1;
    nstate=3;
    StartRelease(); 
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







