
char sample[32] = "32 characters test message. lol\n";
bool toSend = true;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(52, OUTPUT);
}

void loop() {
  char buf[32];
  
  // Read input from the serial monitor as well
  if (Serial.available()) {
    Serial1.print((char)Serial.read());
  }
  
  // Repeatedly sends the sample message. If not all 32 bytes are received the program will freeze up as of now.
  // Additionally there is currently no error detection. We are simply measuring the latency of 32 bytes in and out.
  if (toSend) {
    Serial1.print(sample); // Send the sample message
    toSend = false; // Don't send another message for now
    digitalWrite(52, HIGH); // Set digital pin to high for the serial analyzer
  }

  if (Serial1.available() == 32) { // Wait for 32 bytes to be available
    Serial1.readBytes(buf, 32); // Read 32 bytes
    digitalWrite(52, LOW); // Set digital pin to low for the serial analyzer
    Serial.print(buf); // Print out the test message to the serial monitor
    toSend = true; // Send another message
  }
}
