int count = 0;
int total = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    Serial1.write(Serial.read());
  }
  
  if(Serial1.available() > 0) {

    int incoming = Serial1.read();

    // eof display count and exit
    if (incoming == '#') {
      Serial.print("Total bytes sent/recieved: ");
      Serial.println(total);
      delay(100);
      exit(0);
    }

    // create new line when longer than 30 bytes
    if (count > 0 && count % 30 == 0) {
      Serial.println();
    }

    // increment total and adjust count
    total += 1;
    count = (incoming == '\n') ? 0 : count + 1;

    // write the byte
    Serial.write(incoming);
  }
}
