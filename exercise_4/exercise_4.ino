
#define X_0 502
#define ACC 200.0 // Acceleration factor
#define DEADZONE 10

int LED = 13;
int xPin = A0;

float alpha = 0.8;
int x = X_0;

float pwm = 127.0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  x = alpha * analogRead(xPin) + (1 - alpha) * x;

  if (x > X_0 + DEADZONE || x < X_0 - DEADZONE) {
    int rateOfChange = (x - X_0);
    pwm = getPWMValue(rateOfChange);
  }

  Serial.println(pwm);
  analogWrite(LED, pwm);
}

float getPWMValue(int rateOfChange) {
  if(rateOfChange < 0){
    return max(pwm - abs(rateOfChange)/ACC, 0.0);
  } else {
    return min(pwm + abs(rateOfChange)/ACC, 255.0);
  }
}
