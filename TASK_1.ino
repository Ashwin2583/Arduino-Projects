void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT); //Green
  pinMode(10, OUTPUT); //Yelllow
  pinMode(11, OUTPUT); //Red
}

void loop() {
  // put your main code here, to run repeatedly:
  //Green
  digitalWrite(9, HIGH);
  delay(5000);
  digitalWrite(9,LOW);
  //Yellow
  digitalWrite(10, HIGH);
  delay(2000);
  digitalWrite(10, LOW);
  //Red
  digitalWrite(11, HIGH);
  delay(5000);
  digitalWrite(11, LOW);
}
