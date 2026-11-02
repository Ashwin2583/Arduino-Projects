import serial

# Configure the serial port (update COM port as necessary)
ser = serial.Serial('COM3', 9600, timeout=1)

filename = 'voltage_data.txt'
print(f'Logging voltage data to {filename}. Press Ctrl+C to stop.')

try:
  with open(filename, 'w') as f:
    while True:
      line = ser.readline().decode('latin-1').strip()
      if line:
        f.write(line + '\n')
        print(f'Saved: {line} V')
except KeyboardInterrupt:
  print('\nLogging stopped and file saved successfully.')
finally:
  ser.close()