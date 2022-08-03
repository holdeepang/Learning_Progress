
  // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
//#include <Wire.h>
#include <LCD_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LCD_I2C lcd(0x27,16,2);
//wchar daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};
int relay = 13;
int hr_add = 0;
int hr_minus = 0;
int min_add = 0;
int min_minus = 0;
int s_add = 0;
int s_minus = 0;
int hr_button1 = 2;
int hr_button2 = 5;
int min_button1 = 3;
int min_button2 = 6;
int s_button1 = 4;
int s_button2 = 7;
int set_button = 9;
int reset_button = 8;
int hr = 0;
int minut = 0;
int s = 0;
int sett = 0;
int reset = 0;
bool alarm_set = false;
int duration = 10;

void setup () {
  if (! rtc.begin()) {
    lcd.print("No RTC !");
  }
  if (! rtc.isrunning()) {
    lcd.print("Error !");
    rtc.adjust(DateTime(2022,6,20,17,36,25));
  }
  lcd.begin();
  lcd.backlight();
  pinMode(relay, OUTPUT);
  pinMode(hr_button1, INPUT);
  pinMode(hr_button2, INPUT);
  pinMode(min_button1, INPUT);
  pinMode(min_button2, INPUT);
  pinMode(s_button1, INPUT);
  pinMode(s_button2, INPUT);
  pinMode(set_button, INPUT);
  pinMode(reset_button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
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
  if (now.hour() == hr && now.second() <= s+duration && alarm_set == true) { 
    solenoid_flow();
  } else { // force shut after certain time to prevent leakage
    solenoid_shut();
  }
}

void set_time() {
    hr_add = digitalRead(hr_button1);
    hr_minus = digitalRead(hr_button2);
    min_add = digitalRead(min_button1);
    min_minus = digitalRead(min_button2);
    s_add = digitalRead(s_button1);
    s_minus = digitalRead(s_button2);
    sett = digitalRead(set_button);
    reset = digitalRead(reset_button);
    if (hr_add == 0) {
      hr++;
      alarm_set = false;
    }
    if (hr_minus == 0) {
      hr--;
      alarm_set = false;
    }
    if (min_add == 0) {
      minut++;
      alarm_set = false;
    }
    if (min_minus == 0) {
      minut--;
      alarm_set = false;
    }
    if (s_add == 0) {
      s++;
      alarm_set = false;
    }
    if (s_minus == 0) {
      s--;
      alarm_set = false;
    }
    if (hr == 24) {
      hr = 0;
    } else if (hr < 0) {
      hr = 23;
    }
    if (minut == 60) {
      minut = 0;
    } else if (minut < 0) {
      minut = 59;
    }
    if (s == 60) {
      s = 0;
    } else if (s < 0) {
      s = 59;
    }
    if (sett == 0) {
      alarm_set = true;
      lcd.setCursor(8,0);
      lcd.print("Set!");
      delay(500);
    }
    if (reset == 0) {
      hr = 0;
      minut = 0;
      s = 0;
      alarm_set = false;
      lcd.setCursor(8,0);
      lcd.print("Reset!");
      delay(500);
    }
    lcd.setCursor(0,0);
    lcd.print(hr);
    lcd.print(":");
    lcd.print(minut);
    lcd.print(":");
    lcd.print(s);
    delay(150);
    lcd.clear();  
}

void loop () {
  set_time();
  alarm();
}
