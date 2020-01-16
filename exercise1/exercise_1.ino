int eof = 35; // #
int count = 0;
int total;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    Serial1.write(Serial.read());
  }
  if(Serial1.available() > 0) {
    
    if (count > 0 && count % 30 == 0) {
      Serial.println();
    }

    int incoming = Serial1.read();

    if (incoming == eof) {
      Serial.print("Total bytes sent/recieved: ");
      Serial.println(total);
      delay(100);
      exit(0);
    } else if (incoming == '\n') {
      count = 0;
    } else {
      count += 1;
    }
    total += 1;
    Serial.write(incoming);
  }
}
