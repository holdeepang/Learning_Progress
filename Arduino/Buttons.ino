int val1,val2,val3;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = digitalRead(2);
  val2 = digitalRead(3);
  val3 = digitalRead(4);
  Serial.print(val1);
  Serial.print(val2);
  Serial.println(val3);
  delay(1000);
}
