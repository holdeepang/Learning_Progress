
  // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
//#include <Wire.h>
#include <LCD_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LCD_I2C lcd(0x27,16,2);
//wchar daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};
int hr_button = 2;
int dura_button = 3;
int set_button = 4;
int reset_button = 5;
int manual_button = 6;
int relay = 7;
int hr = 0;
int dura = 10;
int hr_add = 0;
int dura_add = 0;
int sett = 0;
int reset = 0;
int manual = 0;
bool alarm_set = false;
bool manual_set = 0;

void setup () {
  if (! rtc.begin()) {
    lcd.print("No RTC !");
  }
  if (! rtc.isrunning()) {
    lcd.print("Error !");
    rtc.adjust(DateTime(2022,7,4,12,29,25));
  }
  lcd.begin();
  lcd.backlight();
  pinMode(relay, OUTPUT);
  pinMode(hr_button, INPUT);
  pinMode(dura_button, INPUT);
  pinMode(set_button, INPUT);
  pinMode(reset_button, INPUT);
  pinMode(manual_button, INPUT);
  //rtc.adjust(DateTime(2022,7,4,12,29,0));
}

void solenoid_flow(){
  digitalWrite(relay, HIGH);
  lcd.setCursor(11,1);
  lcd.print("Flow");
}

void solenoid_shut(){
  digitalWrite(relay, LOW);
  lcd.setCursor(11,1);
  lcd.print("Shut");
}

void alarm(){
  DateTime now = rtc.now();
  lcd.setCursor(0,1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  //delay(1000);
  if (now.hour() == hr && now.second() <= dura && alarm_set == true) { 
    solenoid_flow();
  } else { // force shut after certain time to prevent leakage
    //solenoid_shut();
    manual_press();
  }
}

void manual_press(){
    manual = digitalRead(manual_button);
    if (manual == 0) {
      manual_set = 1 - manual_set;
    } 
    if (manual_set) {
      solenoid_flow();
    } else {
      solenoid_shut();
    }
    alarm_set = false;
}

void set_time() {
    hr_add = digitalRead(hr_button);
    dura_add = digitalRead(dura_button);
    sett = digitalRead(set_button);
    reset = digitalRead(reset_button);
    if (hr_add == 0) {
      hr++;
      if (hr == 24) {
        hr = 0;
      }
      alarm_set = false;
    }
    if (dura_add == 0) {
      dura += 10;
      if (dura > 30) {
        dura = 10;
      }
      alarm_set = false;
      lcd.setCursor(4,0);
      lcd.print("+");
      lcd.print(dura);
      lcd.print("s");
    }
    if (sett == 0) {
      alarm_set = true;
      lcd.setCursor(8,0);
      lcd.print("Set!");
      delay(500);
    }
    if (reset == 0) {
      hr = 0;
      dura = 10;
      alarm_set = false;
      lcd.setCursor(8,0);
      lcd.print("Reset!");
      delay(500);
    }
    lcd.setCursor(0,0);
    if (hr <= 12) {
      lcd.print(hr);
      lcd.print("AM ");
    } else {
      lcd.print(hr-12);
      lcd.print("PM ");
    }

    delay(150);
    lcd.clear();  
}


void loop () {
  set_time();
  alarm();   
}
