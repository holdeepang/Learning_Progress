
#include <Wire.h>
#include <DS1307RTC.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

tmElements_t tm;

void setup() {
  lcd.begin();
  lcd.backlight();
}

void loop() {
  if (RTC.read(tm)) {
    lcd.print("Time= ");
    lcd.print(tm.Hour);
    lcd.print(":");
    lcd.print(tm.Minute);
    lcd.print(":");
    lcd.print(tm.Second);
  } else {
    if (RTC.chipPresent()) {
      lcd.print("Stopped");
    } else {
      lcd.print("Error");
    }
    delay(9000);
  }
  delay(1000);
  lcd.clear();
}
