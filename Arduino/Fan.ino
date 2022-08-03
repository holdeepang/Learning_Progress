int LED = 3;
int fan = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(fan, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  digitalWrite(fan,HIGH);
  delay(5000);
  digitalWrite(fan,LOW);
}
