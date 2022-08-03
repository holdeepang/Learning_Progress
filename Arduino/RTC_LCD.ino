// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LCD_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LCD_I2C lcd(0x27,16,2);
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};

void setup () {
 if (! rtc.begin()) {
   lcd.print("No RTC !");
 }
 if (! rtc.isrunning()) {
   lcd.print("Error !");
   rtc.adjust(DateTime(2022,6,20,4,34,40));
 } 
 lcd.begin();
 lcd.backlight();
 rtc.adjust(DateTime(2022,6,20,17,25,50));
}

void loop () {
 DateTime now = rtc.now();
 lcd.setCursor(0,0);
 lcd.print(now.year(), DEC);
 lcd.print('/');
 lcd.print(now.month(), DEC);
 lcd.print('/');
 lcd.print(now.day(), DEC);
 lcd.print(" (");
 lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
 lcd.print(")");
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
