/*
 * blink.h
 *
 * Created: 2020-02-12 10:36:17 AM
 *  Author: abdullah
 */ 
#include <avr/io.h>

#ifndef BLINK_H_
#define BLINK_H_

#define Disable_Interrupt()    asm volatile ("cli"::)
#define Enable_Interrupt()     asm volatile ("sei"::)
#define NoOperation()		   asm volatile ("nop"::)

void blink(int bit);
void led_init();
void enable_LED(int bit);
void disable_LED(int bit);
void disable_LEDs();

#endif /* BLINK_H_ */