void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char receivedByte = Serial.read();
    if (receivedByte == 's') {
      Serial.write('A');  // Send acknowledgement
    }
  }
}
