#include <LCD_I2C.h>
int Relaypin= 3; // Define input pin for relay
LCD_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  pinMode(Relaypin, OUTPUT); // Define the Relaypin as output pin
  lcd.begin();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Relaypin, HIGH); // Sends high signal 
  lcd.setCursor(0,0);
  lcd.print("ON");
  delay(5000); // Waits for 1 second
  lcd.clear();
  digitalWrite(Relaypin, LOW); // Makes the signal low
  lcd.print("OFF");
  delay(2000); // Waits for 1 second
  lcd.clear();
}
