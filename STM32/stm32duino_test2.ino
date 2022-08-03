

#include <Wire.h>
#include <DS1307RTC.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
#define sensorPin A0
tmElements_t tm;
// pins
int sensorPower = 3;
int hr_button = 6;
int set_button = 7;
int manual_button = 8;
int fan1 = 9;
int fan2 = 10;
int relay = 11;
// values
int hr = 0;
int dura = 30;
int hr_add = 0;
int sett = 0;
int manual = 0;
bool alarm_set = false;
bool done = false;
bool manual_set = 0;
int water_val = 0;
int level1 = 0;
int level2 = 0;
int diff = 0;
int flow_rate = 2000;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(hr_button, INPUT);
  pinMode(set_button, INPUT);
  pinMode(manual_button, INPUT); 
  pinMode(sensorPower, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  digitalWrite(sensorPower, LOW);
  lcd.begin();
  lcd.backlight();
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

void fan_on() {
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
}

void fan_off() {
  digitalWrite(fan1, LOW);
  digitalWrite(fan2, LOW);
}

void set_time() {
    hr_add = digitalRead(hr_button);
    if (hr_add == 1) {
      hr++;
      if (hr == 24) {
        hr = 0;
      }
      alarm_set = false;
    }
    set_press();
    lcd.setCursor(0,0);
    if (hr <= 12) {
      lcd.print(hr);
      lcd.print("AM");
    } else {
      lcd.print(hr-12);
      lcd.print("PM");
    }
    if (alarm_set == true) {
      lcd.print("*");
    }
    delay(150);
    lcd.clear();  
}

void set_press() {
  sett = digitalRead(set_button);
  if (sett == 1) {
    alarm_set = 1 - alarm_set;  
    
    if (alarm_set) {
    lcd.setCursor(8,0);
    lcd.print("Set!");
    } else {
    hr = 0;
    lcd.setCursor(8,0);
    lcd.print("Reset!");
    }    
  }
  
}

void manual_press(){
    manual = digitalRead(manual_button);
    if (manual == 1) {
      manual_set = 1 - manual_set;
      alarm_set = false;
    } 
    if (manual_set) {
      solenoid_flow();
    } else {
      solenoid_shut();
    }  
}

void alarm() {
  if (RTC.read(tm)) {
    lcd.setCursor(0,1);
    lcd.print(tm.Hour);
    lcd.print(":");
    lcd.print(tm.Minute);
    lcd.print(":");
    lcd.print(tm.Second);
  } else {
      lcd.print("Error");
  }
  
  if (tm.Hour == hr && tm.Minute == 0 && tm.Second <= dura && alarm_set == true && done == false) { 
    solenoid_flow();
    // depend on sensor
    level1 = read_water_level();
    delay(flow_rate);
    level2 = read_water_level();
    diff = abs(level2-level1);
    if (diff < 10) { // after 30 sec
      solenoid_shut();
      fan_on();
      done = true;
    } 
  } else { // force shut after certain time to prevent leakage
    manual_press();
  }

  if (tm.Second == 59) {
    display_wl();
    delay(1000);
    lcd.clear();
    if (read_water_level() <= 100) {
      fan_off();
      done = false;
    }
  }
}

int read_water_level() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  water_val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return water_val;             // send current reading
}

void display_wl() {
  lcd.setCursor(9,0);
  lcd.print("WL: ");
  lcd.print(read_water_level());
}

void loop() {
  alarm();
  set_time();
}
