/*
 * Test_WRR.c
 *
 * Created: 2020-02-12 10:34:05 AM
 *  Author: abdullah
 */ 
#include "../os.h"
#include <avr/io.h>
#include "../blink/blink.h"

// Testing Weighted Round Robin
void Task_P1()
{
	for(;;) {
		blink(1);
		Task_Next();
	}
}

void Task_P2()
{
	for(;;) {
		blink(2);
		Task_Next();
	}
}

void Task_P3()
{
	for(;;) {
		blink(3);
		Task_Next();
	}
}

void Task_P4()
{
	for(;;) {
		blink(4);
		Task_Next();
	}
}

void Task_RR0()
{
	for(;;) blink(0);;
}

void Task_RR1()
{
	for(;;) blink(1);;
}

void Task_RR2()
{
	for(;;) blink(2);;
}

void Task_RR3()
{
	for(;;) blink(3);;
}


void a_main()
{
	/* Uncomment the following when you're done with changes*/
	
	Task_Create_WRR(Task_RR0, 0, 1);
	Task_Create_WRR(Task_RR1, 0, 4);
	Task_Create_WRR(Task_RR2, 0, 16);
	Task_Create_RR(Task_RR3, 0);
	
	
	/* Comment the following when you're done with changes*/
	//Task_Create_RR(Task_RR0,0);
	//Task_Create_RR(Task_RR1,0);
	//Task_Create_RR(Task_RR2,0);
	//Task_Create_RR(Task_RR3,0);
}
