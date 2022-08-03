// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LCD_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LCD_I2C lcd(0x27,16,2);
//wchar daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};
const float  OffSet = 0.464 ;
float V, P;
int relay = 3;
int sensor = 0;

void setup () {
 if (! rtc.begin()) {
   lcd.print("No RTC !");
 }
 if (! rtc.isrunning()) {
   lcd.print("Error !");
   rtc.adjust(DateTime(2022,6,14,15,11,35));
 }
 lcd.begin();
 lcd.backlight();
 pinMode(relay, OUTPUT);
}

void solenoid_flow(){
  digitalWrite(relay, HIGH);
  lcd.setCursor(11,0);
  lcd.print("Flow");
}

void solenoid_shut(){
  digitalWrite(relay, LOW);
  lcd.setCursor(11,0);
  lcd.print("Shut");
}


void pressure(){
  V = analogRead(sensor) * 5.00 / 1024;     //Sensor output voltage
  P = (V - OffSet) * 250;             //Calculate water pressure

  lcd.setCursor(9,1);
  lcd.print(P, 1);
  lcd.print(" KPa");
  if (P <= 2) {
    solenoid_shut();
  }
}

void alarm(){
  DateTime now = rtc.now();
  lcd.setCursor(0,0);
  lcd.print(now.year(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  //lcd.print(" (");
  //lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  //lcd.print(")");
  lcd.setCursor(0,1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  delay(1000);
  if (now.second()%10 == 0) {
    solenoid_flow();
  }
  if (now.second() == 59) {
    lcd.clear();
  }
}

void loop () {
  alarm();
  pressure();

}
