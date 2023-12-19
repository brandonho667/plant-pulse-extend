import serial
import csv
from datetime import datetime

# Adjust the serial port based on your Arduino connection
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

# Open CSV file for writing
csv_file = open('arduino_data.csv', 'w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['Timestamp', 'Input', 'Output'])

try:
    while True:
        # Read line from Arduino
        line = ser.readline().decode('utf-8').strip()

        # Check if the line matches the expected format
        if line.startswith("Timestamp:"):
            # Extract values from the line
            timestamp = line.split(',')[0].split(':')[1].strip() # in ms
            input_value = line.split(',')[1].split(':')[1].strip()
            output_value = line.split(',')[2].split(':')[1].strip()

            # Write to CSV file
            csv_writer.writerow([timestamp, input_value, output_value])
            csv_file.flush()  # Ensure data is written immediately

except KeyboardInterrupt:
    print("Program terminated by user.")

finally:
    # Close the serial port and CSV file
    ser.close()
    csv_file.close()