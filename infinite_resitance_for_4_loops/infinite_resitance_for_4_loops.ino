const int analogPin = A0;      // Connected to the voltage divider node (Terminal A)
const float V_IN = 5.0;        // Arduino supply voltage
const float R_REF = 1000.0;    // Known reference resistor value in Ohms (1 kOhm)
const float R_UNIT = 1000.0;   // The base value of R you used on the breadboard (1 kOhm)

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the Serial Monitor to open

  delay(1000); // Short delay for circuit stabilization

  int sensorValue = analogRead(analogPin);
  float v_out = sensorValue * (V_IN / 1023.0); // Voltage across the ladder network (A to B)

  if (v_out >= V_IN) {
    Serial.println("Error: Check circuit connections (V_out equals V_IN).");
    return;
  }

  // Calculate equivalent resistance using the voltage divider formula:
  float r_eq_measured = R_REF * (v_out / (V_IN - v_out));
  float r_eq_theoretical = 2.0 * R_UNIT;

  // Print results exactly once
  Serial.println("=== Project-2: Equivalent Resistance Measurement ===");
  Serial.print("V_out: ");
  Serial.print(v_out);
  Serial.print(" V | Measured R_eq: ");
  Serial.print(r_eq_measured);
  Serial.print(" ohms | Theoretical R_eq: ");
  Serial.print(r_eq_theoretical);
  Serial.println(" ohms");
}

void loop() {
  // Left empty intentionally so nothing repeats.
}