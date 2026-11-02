
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;

// Detection distances in cm
const float startDistance = 30.0;
const float endDistance = 10.0;

// Maximum permitted average speed in cm/s
const float speedLimit = 5.0;

enum State {
  WAITING_FOR_START,
  WAITING_FOR_END,
  DONE
};

State state = WAITING_FOR_START;

unsigned long startTime = 0;
unsigned long endTime = 0;

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

  float distance = duration / 58.0;

  if (distance < 2.0 || distance > 400.0) {
    return -1.0;
  }

  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);

  Serial.println("Speed-Based Alarm System");
  Serial.print("Start distance: ");
  Serial.print(startDistance);
  Serial.println(" cm");

  Serial.print("End distance: ");
  Serial.print(endDistance);
  Serial.println(" cm");

  Serial.print("Speed limit: ");
  Serial.print(speedLimit);
  Serial.println(" cm/s");

  Serial.println("Move object towards sensor.");
}

void loop() {
  if (state == DONE) {
    return;
  }

  float distance = measureDistance();

  if (distance < 0.0) {
    return;
  }

  // Detect the starting point
  if (state == WAITING_FOR_START &&
      distance <= startDistance) {

    startTime = millis();
    state = WAITING_FOR_END;

    Serial.println("Starting point detected.");
    Serial.println("Timer started.");
  }

  // Detect the ending point and calculate speed
  else if (state == WAITING_FOR_END &&
           distance <= endDistance) {

    endTime = millis();

    float elapsedTime =
        (endTime - startTime) / 1000.0;

    float travelledDistance =
        startDistance - endDistance;

    if (elapsedTime > 0.0) {
      float speed = travelledDistance / elapsedTime;

      Serial.println("------------------------");

      Serial.print("Time taken: ");
      Serial.print(elapsedTime, 3);
      Serial.println(" s");

      Serial.print("Distance interval: ");
      Serial.print(travelledDistance, 2);
      Serial.println(" cm");

      Serial.print("Average speed: ");
      Serial.print(speed, 2);
      Serial.println(" cm/s");

      Serial.print("Speed limit: ");
      Serial.print(speedLimit, 2);
      Serial.println(" cm/s");

      if (speed > speedLimit) {
        digitalWrite(buzzerPin, HIGH);

        Serial.println("ALARM! SPEED LIMIT EXCEEDED!");
        Serial.println("Buzzer ON.");
      }
      else {
        digitalWrite(buzzerPin, LOW);

        Serial.println("Speed within limit.");
        Serial.println("Buzzer OFF.");
      }

      Serial.println("------------------------");
    }

    state = DONE;
    Serial.println("Measurement complete.");
    Serial.println("Reset Arduino to repeat.");
  }
}
