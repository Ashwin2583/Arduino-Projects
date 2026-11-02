
import serial
import time
import numpy as np
import matplotlib.pyplot as plt

PORT = "COM3"       # Change to your Arduino port
BAUD = 9600

voltages = []
currents = []

with serial.Serial(PORT, BAUD, timeout=2) as arduino:
    time.sleep(2)

    while True:
        line = arduino.readline().decode(
            "utf-8", errors="ignore"
        ).strip()

        if not line or line.startswith("Voltage"):
            continue

        try:
            voltage, current = map(float, line.split(","))
            voltages.append(voltage)
            currents.append(current)
            print(f"V = {voltage:.4f} V, "
                  f"I = {current:.4f} mA")
        except ValueError:
            continue

        # The Arduino sends 26 measurements per sweep.
        if len(voltages) >= 26:
            break

V = np.array(voltages)
I = np.array(currents)

# Linear fit: I (mA) = slope * V + intercept
slope, intercept = np.polyfit(V, I, 1)
R_estimated = 1000.0 / slope if slope > 0 else float("inf")

plt.scatter(V, I, label="Measured data")
V_fit = np.linspace(V.min(), V.max(), 200)
plt.plot(V_fit, slope * V_fit + intercept,
         label="Linear fit")

plt.xlabel("Voltage across test resistor (V)")
plt.ylabel("Current through test resistor (mA)")
plt.title("Verification of Ohm's Law")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

print(f"Estimated resistance = {R_estimated:.2f} ohms")
print("Slope is: ",slope)
