
#include <LiquidCrystal.h>
#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
Adafruit_LiquidCrystal lcd_1(0x20);
bool booWriteOnce=true;
bool booWhatsUp=false;
long curTime=0;
long temTime=0;
long delTime=1500;

void setup()
{
	Serial.begin(4800);
    Wire.begin(0x22);
  	lcd.begin(16, 2);
    lcd_1.begin(16, 2);
}

void loop()
{   
curTime=millis();
  
if(Serial.available()) 
{
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(Serial.readString()); 
  lcd.print(char(176));
  lcd.print("ms");
}

if(curTime>=temTime)
{ 
  booWriteOnce=true;
  temTime=curTime+delTime;
}
  
if(booWriteOnce&&booWhatsUp)
{    
  lcd_1.noDisplay();
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Martin");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Marinov");
  lcd_1.display();
  booWriteOnce=false;
  booWhatsUp=false;
}
if(booWriteOnce&&!booWhatsUp)
{    
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Zdrasti");
  lcd_1.setCursor(0, 1);
  lcd_1.print("kesten!");
  booWriteOnce=false;
  booWhatsUp=true;
}
delay(15);
}