#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);
int relay = 3;

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  pinMode(relay, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay, HIGH);
  lcd.setCursor(0,0);
  lcd.print("Flow");
  delay(2000);
  digitalWrite(relay, LOW);
  lcd.setCursor(0,0);
  lcd.print("Shut");
  delay(2000);
}
