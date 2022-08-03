
// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;
int level1 = 0;
int level2 = 0;
int diff = 0;

void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  level1 = readSensor();
  Serial.println(level1);
  delay(2000);
  level2 = readSensor();
  Serial.println(level2);
  diff = abs(level2-level1);
  if (diff < 10) { // after 30 sec
    Serial.println("Shut");
    // solenoid_shut();
  } else { // minimum flow 10 sec
    Serial.println("Flow");
  }
  if (level2 <= 100) {
    Serial.println("No Fan");
  }
}

//This is a function us ed to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}
