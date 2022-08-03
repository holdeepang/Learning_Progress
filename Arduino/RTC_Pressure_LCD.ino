// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LCD_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LCD_I2C lcd(0x27,16,2);
const float  OffSet = 0.464 ;
float V, P, temp;

void setup () {
 if (! rtc.begin()) {
   lcd.print("No RTC !");
 }
 /*if (! rtc.isrunning()) {
   lcd.print("Error !");
   rtc.adjust(DateTime(2022,6,16,9,41,10));
 }*/
 lcd.begin();
 lcd.backlight();
}

void pressure(){
  V = analogRead(0) * 5.00 / 1024;     //Sensor output voltage
  P = (V - OffSet) * 250;             //Calculate water pressure
  if (P > temp) {
     temp = P;
  }
  lcd.setCursor(9,0);
  lcd.print(P,1);
  lcd.print(" KPa");
  lcd.setCursor(9,1);
  lcd.print(temp, 1);
  lcd.print(" max");
}

void alarm(){
  DateTime now = rtc.now();
  lcd.setCursor(0,0);
  lcd.print(now.year(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  lcd.setCursor(0,1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  delay(1000);
  if (now.second() == 59) {
    lcd.clear();
  }
}

void loop () {
  alarm();
  pressure();

}
