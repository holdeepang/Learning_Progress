/*
  SimpleRTC
  This sketch shows how to configure the RTC and to display
  the date and time periodically
  Creation 12 Dec 2017
  by Wi6Labs
  Modified 03 Jul 2020
  by Frederic Pillon for STMicroelectronics
  This example code is in the public domain.
  https://github.com/stm32duino/STM32RTC
*/

#include <STM32RTC.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

const byte seconds = 30;
const byte minutes = 9;
const byte hours = 17;
const byte weekDay = 4;
const byte day = 7;
const byte month = 7;
const byte year = 22;

void setup()
{
  Serial.begin(9600);

  // Select RTC clock source: LSI_CLOCK, LSE_CLOCK or HSE_CLOCK.
  // By default the LSI is selected as source.
  //rtc.setClockSource(STM32RTC::LSE_CLOCK);

  rtc.begin(); // initialize RTC 24H format

  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);

  // Set the date
  rtc.setWeekDay(weekDay);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);

  // you can use also
  //rtc.setTime(hours, minutes, seconds);
  //rtc.setDate(weekDay, day, month, year);
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
}

void loop()
{
  // Print date...
  lcd.setCursor(0,0);
  lcd.print(rtc.getDay());
  lcd.print("/");
  lcd.print(rtc.getMonth());
  lcd.print("/20");
  lcd.print(rtc.getYear());

  // ...and time
  lcd.setCursor(0,1);
  lcd.print(rtc.getHours());
  lcd.print(":");
  lcd.print(rtc.getMinutes());
  lcd.print(":");
  lcd.print(rtc.getSeconds());
  
  delay(1000);
}
