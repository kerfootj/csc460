#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(8);
  myservo.writeMicroseconds(1500);
  Serial.begin(9600);

}

void loop() {
//   put your main code here, to run repeatedly:
  for(int i = 1000; i < 2000; i++) {
    myservo.writeMicroseconds(i);
    delay(2);
  }

  for(int i = 2000; i>1000; i--) {
    myservo.writeMicroseconds(i);
    delay(3);
  }
}
