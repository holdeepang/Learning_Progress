#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);
const float  OffSet = 0.464 ;
float V, P;

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Connect sensor to Analog 0
  V = analogRead(0) * 5.00 / 1024;     //Sensor output voltage
  P = (V - OffSet) * 250;             //Calculate water pressure

  lcd.setCursor(0,0);
  lcd.print("Volt: ");
  lcd.print(V,1);
  lcd.print(" V");
  lcd.setCursor(0,1); 
  lcd.print("Press: ");
  lcd.print(abs(P), 1);
  lcd.print(" KPa");

  delay(500);
}
