
const int Nmax = 10000;

double S1 = 0.0;
double S2 = 0.0;
double S3 = 0.0;

void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("N,S1,S2,S3");

  for (int n = 1; n <= Nmax; n++) {
    // Series 1: sum of (-1)^n / n
    if (n % 2 == 0) {
      S1 += 1.0 / n;
    } else {
      S1 -= 1.0 / n;
    }

    // Series 2: sum of 1/n
    S2 += 1.0 / n;

    // Series 3: sum of 1/n^2
    S3 += 1.0 / ((double)n * n);

    Serial.print(n);
    Serial.print(",");
    Serial.print(S1, 8);
    Serial.print(",");
    Serial.print(S2, 8);
    Serial.print(",");
    Serial.println(S3, 8);

    delay(2);
  }
}

void loop() {
  // Calculation ends after Nmax terms.
}
