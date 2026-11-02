import time
import matplotlib.pyplot as plt
import serial

# --- CONFIGURATION ---
PORT = 'COM3'  # Update to your Arduino's COM port
BAUD = 9600
RESISTOR_OHMS = (
    330.0  # Change this to your exact series resistor value (in Ohms)
)
filename = 'iv_data.txt'

print(f'Connecting to {PORT}...')
print(
    'Slowly turn your potentiometer knob from minimum to maximum, then press'
    ' Ctrl+C to stop and plot.'
)

voltages_vd = []
currents_ma = []

try:
  ser = serial.Serial(PORT, BAUD, timeout=1)
  time.sleep(2)  # Allow connection to initialize

  with open(filename, 'w') as f:
    f.write('Vin_V,Vd_V,Id_mA\n')  # CSV Header

    while True:
      line = ser.readline().decode('utf-8', errors='ignore').strip()
      if line:
        parts = line.split(',')
        if len(parts) == 2:
          try:
            vin = float(parts[0])
            vd = float(parts[1])

            # Calculate diode current using Ohm's Law: I = (Vin - Vd) / R
            # Result in Amperes, multiplied by 1000 to get milliamperes (mA)
            current_ma = ((vin - vd) / RESISTOR_OHMS) * 1000.0
            if current_ma < 0:
              current_ma = 0.0

            # Write to file and store in lists for plotting
            f.write(f'{vin},{vd},{current_ma}\n')
            voltages_vd.append(vd)
            currents_ma.append(current_ma)

            print(
                f'Vin: {vin:.2f}V | Diode V_d: {vd:.2f}V | Current I_d:'
                f' {current_ma:.2f} mA'
            )
          except ValueError:
            pass

except KeyboardInterrupt:
  print('\nData logging stopped by user.')
finally:
  if 'ser' in locals() and ser.is_open:
    ser.close()

# --- PLOTTING THE I-V CURVE ---
if voltages_vd and currents_ma:
  plt.figure(figsize=(8, 5))
  plt.plot(
      voltages_vd,
      currents_ma,
      'ro-',
      linewidth=1.5,
      markersize=4,
      label='1N4007 Diode',
  )
  plt.title('Forward Bias I-V Characteristic Curve')
  plt.xlabel('Diode Voltage $V_d$ (V)')
  plt.ylabel('Diode Current $I_d$ (mA)')
  plt.grid(True, linestyle='--', alpha=0.6)
  plt.axhline(0, color='black', linewidth=0.8)
  plt.axvline(0, color='black', linewidth=0.8)
  plt.legend()
  plt.tight_layout()

  # Save the plot image and show it
  plt.savefig('iv_curve_plot.png')
  print("Plot saved successfully as 'iv_curve_plot.png'.")
  plt.show()
else:
  print('No data collected to plot.')