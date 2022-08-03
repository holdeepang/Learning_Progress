#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

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

void setup()
{
    lcd.begin(); 
    lcd.backlight();
    pinMode(hr_button1, INPUT);
    pinMode(hr_button2, INPUT);
    pinMode(min_button1, INPUT);
    pinMode(min_button2, INPUT);
    pinMode(s_button1, INPUT);
    pinMode(s_button2, INPUT);
    pinMode(set_button, INPUT);
    pinMode(reset_button, INPUT);
    //Serial.begin(9600);
}

void loop()
{
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
    }
    if (hr_minus == 0) {
      hr--;
    }
    if (min_add == 0) {
      minut++;
    }
    if (min_minus == 0) {
      minut--;
    }
    if (s_add == 0) {
      s++;
    }
    if (s_minus == 0) {
      s--;
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
      lcd.setCursor(8,0);
      lcd.print("Set!");
    }
    if (reset == 0) {
      lcd.setCursor(8,0);
      lcd.print("Reset!");
      hr = 0;
      minut = 0;
      s = 0;
    }
    lcd.setCursor(0,0);
    lcd.print("Alarm: ");
    lcd.setCursor(0,1);
    lcd.print(hr);
    lcd.print(":");
    lcd.print(minut);
    lcd.print(":");
    lcd.print(s);
    delay(150);
    lcd.clear();

}
