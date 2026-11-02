
const int pwmPin = 9;
const int voltageTopPin = A1;
const int voltageBottomPin = A0;

const float Vref = 5.0;
const float ADCmax = 1023.0;
const float Rsense = 220.0;

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);
  analogReference(DEFAULT);
  delay(1000);

  Serial.println("Voltage_V,Current_mA");
}

void loop() {
  for (int duty = 0; duty <= 255; duty += 10) {
    analogWrite(pwmPin, duty);
    delay(100);

    const int N = 30;
    long sumTop = 0;
    long sumBottom = 0;

    for (int i = 0; i < N; i++) {
      sumTop += analogRead(voltageTopPin);
      sumBottom += analogRead(voltageBottomPin);
      delay(2);
    }

    float adcTop = sumTop / (float)N;
    float adcBottom = sumBottom / (float)N;

    float Vtop = adcTop * Vref / ADCmax;
    float Vbottom = adcBottom * Vref / ADCmax;

    float Vtest = Vtop - Vbottom;
    float current_mA = (Vbottom / Rsense) * 1000.0;

    Serial.print(Vtest, 4);
    Serial.print(",");
    Serial.println(current_mA, 4);

    delay(300);
  }

  analogWrite(pwmPin, 0);
  while (true) {
    // Reset Arduino to run another sweep.
  }
}
