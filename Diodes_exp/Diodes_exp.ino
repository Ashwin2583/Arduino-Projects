const int pinVin = A0; // Connected to potentiometer wiper (Total Voltage)
const int pinVd  = A1; // Connected to diode anode (Diode Voltage)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawVin = analogRead(pinVin);
  int rawVd  = analogRead(pinVd);

  // Convert ADC values (0-1023) to voltages (0-5V)
  float vin = rawVin * (5.0 / 1023.0);
  float vd  = rawVd  * (5.0 / 1023.0);

  // Send comma-separated values to Serial
  Serial.print(vin);
  Serial.print(",");
  Serial.println(vd);

  delay(200); // Sampling interval as you slowly turn the knob
}