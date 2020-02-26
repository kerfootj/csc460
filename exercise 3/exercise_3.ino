void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long start = millis();
  
  int i;
  for (i = 0; i < 256; i++) {
     analogWrite(13, i);
     delay(6);
  }

  for (i = 255; i >=0; i--) {
    analogWrite(13, i);
    delay(6);
  }

  Serial.print(millis() - start); // 3080ms ~3s
  
}
