int Relaypin= 3; // Define input pin for relay

void setup() {
  // put your setup code here, to run once:
  pinMode(Relaypin, OUTPUT); // Define the Relaypin as output pin
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Relaypin, HIGH); // Sends high signal 
  Serial.println("ON");
  delay(5000); // Waits for 1 second
  digitalWrite(Relaypin, LOW); // Makes the signal low
  Serial.println("OFF");
  delay(2000); // Waits for 1 second
}
