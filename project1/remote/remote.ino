#include "scheduler.h"
#include <Servo.h>

#define SERVO_MAX 2300
#define SERVO_MIN 600
#define BUF_SIZE 25
#define HORZ_PIN 9
#define VERT_PIN 10
#define LED_PIN 11
#define I_PIN 24

#define LOG false

Servo horz;
Servo vert;

int horzus = 1000;
int vertus = 1000;

int data[3];
char buff[BUF_SIZE];



void readData() {
  bool fin = false;
  bool corrupt = false;
  int buffPos = 0;
  // Read our data packet that starts with ( and ends with )
  if(!Serial1.available()) return;
  while (true) {
    if (Serial1.available()) {
      char c = Serial1.read();
      if (c == '(') { // Wait for packet start character
        break;
      }
    }
  }

  while (true) {
    if (Serial1.available()) {
      char c = Serial1.read();
      switch (c) {
        case '(':
          corrupt = true;
        case ')':
          fin = true;
          break;
        default:
          buff[buffPos] = c;
          buffPos++;
          break;
      }
    }
    if (fin) {
      break;
    }
  }

  if (corrupt) {
    clearBuff();
    return;
  }

  String raw_data[3] = {"", "", ""};
  int rawDataPos = 0;
  for (int i = 0; i < buffPos; i++) {
    char c = buff[i];
    if (c == ',') {
      rawDataPos++;
    } else {
      raw_data[rawDataPos] = raw_data[rawDataPos] + c;
    }
  }

  data[0] = raw_data[0].toInt();
  data[1] = raw_data[1].toInt();
  data[2] = raw_data[2].toInt();
  clearBuff();
  if(LOG) printVals();
  updateServos();
  return;
}

void clearBuff() {
  for (int i = 0; i < BUF_SIZE; i++) {
    buff[i] = 0;
  }
}

void printVals() {
  Serial.println("(" + String(data[0]) + "," + String(data[1]) + "," + String(data[2]) + ")");
}

void updateServos() {
  horzus = min(max(horzus + data[0], SERVO_MIN), SERVO_MAX);
  vertus = min(max(vertus + data[1], SERVO_MIN), SERVO_MAX);
  int led_val = data[2] == -1 ? 0 : 255;
  horz.writeMicroseconds(horzus);
  vert.writeMicroseconds(vertus);
  analogWrite(LED_PIN, led_val);
}

void idle(uint32_t period) {
  digitalWrite(I_PIN, HIGH);
  if(LOG) Serial.println("idle " + String(period, DEC));
  delay(period);
  digitalWrite(I_PIN, LOW);
}

void setup() {
  // put your setup code here, to run once:
  horz.attach(HORZ_PIN);
  vert.attach(VERT_PIN);
  int horzus = SERVO_MIN;
  int vertus = SERVO_MIN;

  pinMode(LED_PIN, OUTPUT);
  pinMode(I_PIN, OUTPUT);

  Serial1.begin(9600);
  while (!Serial1);
  Serial.begin(9600);
  while (!Serial);
  analogWrite(LED_PIN, 0);

  Scheduler_StartTask(0, 100, readData);

}

void loop() {
  int period = Scheduler_Dispatch();
  if (period) idle(period);
}
