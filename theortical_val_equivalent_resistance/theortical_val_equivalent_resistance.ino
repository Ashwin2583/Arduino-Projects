const int analogPin = A0;      // Connected to the voltage divider node (Terminal A)
const float V_IN = 5.0;        // Arduino supply voltage
const float R_REF = 1000.0;    // Known reference resistor value in Ohms (1 kOhm)
const float R_UNIT = 1000.0;   // The base value of R used on the breadboard (1 kOhm)
const int numSamples = 50;     // Number of samples for hardware averaging

// Function to calculate equivalent resistance by adding n stages from the load side
float getLadderResistance(int n, float R) {
  // Start with just the final shunt resistor (2R) at the end of n stages
  float r_eq = 2.0 * R;
  
  // Add preceding stages one by one
  for (int i = 1; i < n; i++) {
    // In parallel with 2R, then in series with R
    float parallel_val = (2.0 * R * r_eq) / (2.0 * R + r_eq);
    r_eq = R + parallel_val;
  }
  
  // First stage includes the initial series resistor R
  // If n = 1, it's just R in series with the shunt 2R
  float final_parallel = (2.0 * R * r_eq) / (2.0 * R + r_eq);
  return R + final_parallel;
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open

  delay(1000); // Short delay for circuit stabilization

  // --- 1. HARDWARE MEASUREMENT WITH AVERAGING ---
  long sumSensorValue = 0;
  for (int i = 0; i < numSamples; i++) {
    sumSensorValue += analogRead(analogPin);
    delay(5); 
  }
  
  float avgSensorValue = (float)sumSensorValue / numSamples;
  float v_out = avgSensorValue * (V_IN / 1023.0); 

  if (v_out >= V_IN) {
    Serial.println("Error: Check circuit connections (V_out equals V_IN).");
    return;
  }

  float r_eq_measured = R_REF * (v_out / (V_IN - v_out));
  float r_eq_theoretical = 2.0 * R_UNIT; 

  // --- 2. CONVERGENCE CALCULATION FOR STAGES ---
  int stages = 1;
  float calculated_req = 0;
  
  while (stages <= 50) {
    calculated_req = getLadderResistance(stages, R_UNIT);
    // Check if it has converged to within 1 ohm of the infinite theoretical limit (2R)
    if (fabs(calculated_req - r_eq_theoretical) < 0.01) { 
      break;
    }
    stages++;
  }

  // --- 3. PRINT RESULTS ---
  Serial.println("=== Project-2: Equivalent Resistance & Convergence Analysis ===");
  Serial.print("Averaged V_out: ");
  Serial.print(v_out);
  Serial.println(" V");
  
  Serial.print("Measured R_eq: ");
  Serial.print(r_eq_measured);
  Serial.println(" ohms");
  
  Serial.print("Theoretical Infinite R_eq (2R): ");
  Serial.print(r_eq_theoretical);
  Serial.println(" ohms");

  Serial.println("-------------------------------------------------------------");
  Serial.print("Calculated stages (n) needed for convergence to 2R: ");
  Serial.println(stages);
  Serial.print("Resistance value at stage ");
  Serial.print(stages);
  Serial.print(": ");
  Serial.print(calculated_req, 2);
  Serial.println(" ohms");
}

void loop() {
  // Left empty intentionally so it only runs once per reset.
}