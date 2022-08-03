#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

/*
* When using lcd.print() (and almost everywhere you use string literals),
* is a good idea to use the macro F(String literal).
* This tells the compiler to store the string array in the flash memory
* instead of the ram memory. Usually you have more spare flash than ram.
* More info: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
*/

void setup()
{
    lcd.begin();
    lcd.backlight();
}

void loop()
{
    lcd.backlight();
    lcd.setCursor(2,0); // (x,y) where x is column and y is row
    lcd.print("Hello World !");
    delay(2000);
    lcd.clear();
    
    // Scroll left and right
    lcd.setCursor(1, 0);
    lcd.print("Left!");
    for (int i = 0; i < 5; i++)
    {
        lcd.scrollDisplayLeft();
        delay(500);
    }
    lcd.clear();

    lcd.setCursor(9, 0);
    lcd.print("Right!");
    for (int i = 0; i < 6; i++)
    {
        lcd.scrollDisplayRight();
        delay(500);
    }
    lcd.clear();

    lcd.setCursor(5,0);
    lcd.print("Clear !");
    // Flashing the backlight
    for (int i = 0; i < 5; ++i)
    {
        lcd.backlight();
        delay(100);
        lcd.noBacklight();
        delay(100);
    }
    lcd.clear();
    lcd.backlight();

    //Blink without cursor
    lcd.setCursor(0, 0);
    lcd.blink();
    lcd.print("Blink");
    delay(3000);
    lcd.noBlink();
    lcd.clear();

    lcd.setCursor(4,0);
    lcd.print("Bye Bye");
    delay(500);
    lcd.noBacklight();
    lcd.clear();
    delay(1500);
}
