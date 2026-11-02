
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW);

  Serial.println("Ultrasonic Distance Measurement");
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  unsigned long duration =
      pulseIn(echoPin, HIGH, 30000UL);

  if (duration == 0) {
    return -1.0;
  }

  return duration / 58.0;
}

void loop() {
  float sum = 0.0;
  int count = 0;

  for (int i = 0; i < 5; i++) {
    float d = measureDistance();

    if (d >= 2.0 && d <= 400.0) {
      sum += d;
      count++;
    }

    delay(100);
  }

  if (count > 0) {
    float x = sum / count;

    Serial.print("Distance x = ");
    Serial.print(x, 2);
    Serial.println(" cm");

    Serial.print("Distance (x - 2) = ");
    Serial.print(x - 2.0, 2);
    Serial.println(" cm");
  } else {
    Serial.println("No valid echo. Check sensor or target.");
  }

  Serial.println("----------------------");
  delay(500);
}
