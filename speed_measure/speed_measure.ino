
const int trigPin = 9;
const int echoPin = 10;

const float startDistance = 30.0; // cm
const float endDistance   = 10.0; // cm

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

  Serial.println("Object Speed Measurement");
  Serial.println("Move object towards sensor.");
  Serial.println("Start: 50 cm | End: 30 cm");
}

void loop() {
  if (state == DONE) {
    return;
  }

  float distance = measureDistance();

  if (distance < 0.0) {
    return;
  }

  if (state == WAITING_FOR_START &&
      distance <= startDistance) {

    startTime = millis();
    state = WAITING_FOR_END;

    Serial.println("Starting point detected!");
    Serial.println("Timer started.");
  }

  else if (state == WAITING_FOR_END &&
           distance <= endDistance) {

    endTime = millis();

    float elapsedTime =
        (endTime - startTime) / 1000.0;

    float travelledDistance =
        startDistance - endDistance;

    if (elapsedTime > 0.0) {
      float speed = travelledDistance / elapsedTime;

      Serial.println("Ending point detected!");
      Serial.print("Time taken = ");
      Serial.print(elapsedTime, 3);
      Serial.println(" seconds");

      Serial.print("Distance travelled = ");
      Serial.print(travelledDistance, 2);
      Serial.println(" cm");

      Serial.print("Average speed = ");
      Serial.print(speed, 2);
      Serial.println(" cm/s");

      Serial.print("Average speed = ");
      Serial.print(speed / 100.0, 3);
      Serial.println(" m/s");
    }

    state = DONE;
    Serial.println("Measurement complete.");
    Serial.println("Reset Arduino to repeat.");
  }
}
