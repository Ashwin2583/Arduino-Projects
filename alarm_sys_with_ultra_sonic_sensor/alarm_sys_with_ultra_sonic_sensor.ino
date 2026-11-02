const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

// Distance threshold for the security alarm (in centimeters)
const int alarmDistance = 20; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm (Speed of sound is ~0.034 cm/microsecond, divided by 2 for round trip)
  float distance = duration * 0.034 / 2.0;

  // Print results to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if object is within the security alarm limit
  if (distance > 0 && distance < alarmDistance) {
    // Intrusion detected! Sound the buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Fast beeping when close
  } else {
    // Safe state: turn buzzer off
    digitalWrite(buzzerPin, LOW);
  }

  delay(100); // Delay between measurements
}