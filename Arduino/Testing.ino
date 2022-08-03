   // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LCD_I2C.h>
LCD_I2C lcd(0x27,16,2);
const float  OffSet = 0.464 ;
float V, P;
int relay = 3;
int sensor = 0;

void setup () {
 lcd.begin();
 lcd.backlight();
 pinMode(relay, OUTPUT);
}

void solenoid_flow(){
  digitalWrite(relay, HIGH);
  lcd.setCursor(5,0);
  lcd.print("Flow");
}

void solenoid_shut(){
  digitalWrite(relay, LOW);
  lcd.setCursor(5,0);
  lcd.print("Shut");
}


void pressure(){
  V = analogRead(sensor) * 5.00 / 1024;     //Sensor output voltage
  P = (V - OffSet) * 250;             //Calculate water pressure

  lcd.setCursor(5,1);
  lcd.print(abs(P), 1);
  lcd.print(" KPa");
}

void loop () {
  pressure();
  //delay(1000);
  solenoid_shut();
  delay(5000);
  solenoid_flow();
  delay(5000);
}
