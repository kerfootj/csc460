#include <LiquidCrystal.h>

int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned int ms = 0;
unsigned int sec = 0;
unsigned int mins = 0;

ISR(TIMER0_COMPA_vect) {
  digitalWrite(53, LOW);
  ms += 1;
  if (ms >= 1000) {
    ms = 0;
    if (++sec >= 60) {
      mins += 1;
      sec = 0;
    }
  }
  digitalWrite(53, HIGH);
}

void configureTimer() {
  //set timer0 interrupt at 1kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR0A = 249;// = (16*10^6) / (1000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();
}


int main(void) {

  configureTimer();

  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  
  char mills[4];
  char seconds[4];
  char minutes[4];
  
  for(;;) {
    lcd.clear();

    itoa(ms, mills, 10);
    itoa(sec, seconds, 10);
    itoa(mins, minutes, 10);

    lcd.write(minutes);
    lcd.print(":");
    lcd.write(seconds);
    lcd.print(":");
    lcd.write(mills);
    
  }
}
