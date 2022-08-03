#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

void setup()
{
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(2,0);
    lcd.print("Hello World !"); // You can make spaces using well... spaces
    delay(2000);
    lcd.clear();
    delay(500);
}
