
import serial
import time

PORT = "COM3"  # Change if your Arduino uses another port
BAUD = 9600

try:
    with serial.Serial(PORT, BAUD, timeout=2) as arduino:
        print("Connected to Arduino.")
        print("Waiting for serial data...")

        # Arduino may reset when the serial connection opens.
        time.sleep(2)
        arduino.reset_input_buffer()

        for i in range(15):
            raw = arduino.readline()

            if raw:
                line = raw.decode(
                    "utf-8", errors="replace"
                ).strip()
                print("Received:", repr(line))
            else:
                print("No data received within 2 seconds.")

except serial.SerialException as e:
    print("Serial connection error:", e)
