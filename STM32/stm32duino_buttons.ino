//#define button PB1

int button = 6;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(button);
  Serial.println(val);
  delay(1000);
}
