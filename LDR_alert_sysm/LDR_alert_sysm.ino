const int ldrPin = A0;    // Analog pin connected to LDR voltage divider
const int ledPin = 8;     // Digital pin for the alert LED

// Threshold value (adjust based on your room's ambient lighting)
const int threshold = 500; 

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  // Print current reading to Serial Monitor for calibration
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Security Trigger: If light drops below threshold (intrusion / shadow)
  if (ldrValue < threshold) {
    // Flash the LED alert
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  } else {
    // Normal state: LED off
    digitalWrite(ledPin, LOW);
  }
  
  delay(100); // Small delay between checks
}