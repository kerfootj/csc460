#include "scheduler.h"
#include <LiquidCrystal.h>

#define DEBUG false

#define I_PIN 24
#define L_PIN 52
#define X_PIN A8
#define Y_PIN A9
#define S_PIN A10
#define X_0 502
#define Y_0 512
#define DEADZONE 10
#define ALPHA 0.8
#define DELTA 8

int x = X_0;
int y = Y_0;
int swtch = 0;
int on = -1;
bool toggle = false;
bool light = false;

int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int format(int value, int zerod) {
  int norm = value - zerod;
  if (norm < 10 && norm > -10) {
    return 0;
  }
  return min(max(int(norm / DELTA), -62), 62);
}

void getControls() {
  x = ALPHA * analogRead(X_PIN) + (1 - ALPHA) * x;
  y = ALPHA * analogRead(Y_PIN) + (1 - ALPHA) * y;
  swtch = analogRead(S_PIN);

  if (swtch < 50 && !toggle) {
    on *= -1;
    toggle = true;
  } else if (swtch >= 50 && toggle) {
    toggle = false;
  }

  if (DEBUG) {
    Serial.println(String("(" + String(format(x, X_0), DEC) + "," + String(format(y, Y_0), DEC) + "," + String(on, DEC) + ")"));
  }
  
  Serial2.print(String("(" + String(format(x, X_0), DEC) + "," + String(format(y, Y_0), DEC) + "," + String(on, DEC) + ")"));
}

void detectLight() {
  light = digitalRead(L_PIN) == 0;

  if (DEBUG) {
    Serial.println(light);
  }
}

void updateDisplay() {
  lcd.clear();
  // display x,y on topline
  lcd.print(String("X: " + String(x, DEC)));
  lcd.setCursor(8, 0);
  lcd.print(String("Y: " + String(y, DEC)));

  // display switch and light sensor
  lcd.setCursor(0, 1);
  String led = on == 1 ? "On" : "Off";
  lcd.print("S: " + led);
  lcd.setCursor(8, 1);
  String lite = light ? "Yes" : "No";
  lcd.print("L: " + lite);
}

void idle(uint32_t idle_period) {
  digitalWrite(I_PIN, HIGH);
  delay(idle_period);
  digitalWrite(I_PIN, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(S_PIN, INPUT);
  pinMode(L_PIN, INPUT);
  pinMode(I_PIN, OUTPUT);

  lcd.begin(16, 2);
  
  Scheduler_Init();

  Scheduler_StartTask(0, 100, getControls);
  Scheduler_StartTask(0, 100, detectLight);
  Scheduler_StartTask(0, 200, updateDisplay);

}

void loop() {

  uint32_t idlePeriod = Scheduler_Dispatch();
  
  if (idlePeriod) {
    idle(idlePeriod);
  }
}
