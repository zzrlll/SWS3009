import serial

# Open the serial port
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

# Send handshake signal
ser.write(b's')

# Read response from Arduino
response = ser.read()

# Check if handshake is successful
if response == b'A':
    print("Arduino Online")
else:
    print("Handshake failed")

# Close the serial port
ser.close()
