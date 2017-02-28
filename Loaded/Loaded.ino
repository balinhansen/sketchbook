#include <LiquidCrystal.h>

//LiquidCrystal lcd(12, 11, 2, 3, 4, 5);  // Sparkfun 16x2 wtf??!
LiquidCrystal lcd(12, 11, 3, 2, 1, 0);  // Sparkfun 16x2 wtf??!


byte b0[8] = {
  0b00000,
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00000,
  0b00000
};

void setup() {
  // create a new character
  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.noCursor();
  lcd.noAutoscroll();
  lcd.setCursor(0,0);
  lcd.createChar(2,b0);
  //Serial.begin(115200);

}

void loop(){
  static int stat,sent;
  
  if (!sent){
    sent=1;
    lcd.setCursor(0,0);
    lcd.print("Loading ...");
  }
  
  lcd.setCursor(0,1);
  
  if (!stat){
    stat=1;
  }
  
  switch (stat){
    case 1:
    lcd.print("|");
    break;
    case 2:
    lcd.print("/");
    break;
    case 3:
    lcd.print("-");
    break;
    case 4:
    lcd.write(2);
    break;
  }
  stat=stat+1;
  
  if (stat > 4){
    stat=1;
  }
  
  delay(66);
}
