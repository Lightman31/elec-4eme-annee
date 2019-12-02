/* --------------------------------------------------------------- */
/* -------- DEMO CODE --- SEVEN SEGMENT CLOCK -------------------- */
/* ---------------------- USING INTERRUPTS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --------------------------------------------------------------- */
/* --- (c) 2014 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* --- use interrupts given by TMR0 to count the second ---------- */
/* --- use the 4 7-segment displays available on an -------------- */
/* ---  easyPIC 4/5 board from mikroelektronika ------------------ */
/* --------------------------------------------------------------- */
/* --- DISPLAY MM:SS or HH:MM on the 7-segments ------------------ */
/* --------------------------------------------------------------- */

// --- the compulsory header file for HI-TECH C
#include <htc.h>

// --- include the PIC18F4550 description file
//#include <pic18f4550.h>

// set the configuration bits: no code protect, watchdog off etc.
#pragma config WDT = OFF
#pragma config LVP = OFF  //low voltage programming off 
//#pragma config OSC = HS
#pragma config FOSC = HS  // HS oscillator, HS used by USB


// the include the h-file with function prototypes & variables
#include "SevenSeg_PIC18F.h"


/* --------------------------------------------------------------- */
/* -------------- the interrupt function ------------------------- */
/* --------------------------------------------------------------- */
void interrupt irq_handle(void)
{
	// interrupt routine should check first the flags
	if (TMR0IE && TMR0IF)
	{
		// it is TMR0, reset the interrupt FLAG
		TMR0IF=0;
		// decrement the counter
		count1--;
		// if the counter variable is zero, do the desired action
		if (count1==0)
			{
				// the second is here
				sec0++;
				// init the counter with the default value
				count1=count1_start_value;
				// set the flag
				update_time=1;
			}
		return;
	}
}


/* --------------------------------------------------------------- */
/* -------------------- the MAIN function ------------------------ */
/* --------------------------------------------------------------- */
void main (void)
{
/* --------------------------------------------------------------- */
/* ------ call the function that will INITIALIZE the PIC --------- */
/* --------------------------------------------------------------- */
	initMyPIC18F();

/* --------------------------------------------------------------- */
/* ------------- TRAP your code in an INFINITE LOOP -------------- */
/* --------------------------------------------------------------- */
/* --- remember: any program should be "kept" in an infinite loop  */
/* --- because you have no OS, therefore no return(0) ------------ */
/* --------------------------------------------------------------- */
 	while (1)
  	{
/* --------------------------------------------------------------- */
/* --- is it time to update? I mean, was sec0 incremented? ------- */
/* --------------------------------------------------------------- */
	if (update_time)
		{
		// --- yes, update the time
		// --- call the time_update() function
			time_update();
		}
		// --- no, just continue
/* --------------------------------------------------------------- */
/* ------- apply the BCD mask to each DISPLAY -------------------- */
/* --------------------------------------------------------------- */
	// --- apply mask to DISPLAY 0
	dis_data[0]=SevenSegApplyMask(raw_data[0]);
	// --- apply mask to DISPLAY 0
	dis_data[1]=SevenSegApplyMask(raw_data[1]);
	// --- apply mask to DISPLAY 0
	dis_data[2]=SevenSegApplyMask(raw_data[2]);
	// --- apply mask to DISPLAY 0
	dis_data[3]=SevenSegApplyMask(raw_data[3]);

/* --------------------------------------------------------------- */
/* ------- now simply DISPLAY the contents of dis_data[0..3] ----- */
/* --------------------------------------------------------------- */
	SevenSegDisplay(dis_data);	

    } 		// close the infinite while(1) loop

} 			// close of the main function

/* --------------------------------------------------------------- */
/* ----------------- init the PIC18F4550 device ------------------ */
/* --------------------------------------------------------------- */
void initMyPIC18F(void)
{
	// set PORTA as OUTPUT
	TRISA = 0x00;
	// set PORTA digital I/O (no analog pins)
	ADCON1 = 0x0F;
	// reset the port (al zeros)
	PORTA = 0;
	
	// set PORTD as OUTPUT
	TRISD = 0x00;
	// reset the port
	PORTD = 0;
	
	// configure the timer TMR0
	// --- read the datasheet!
	TMR0ON = 1;		// TMR0 ON
	T0CS = 0;		// select clock source => internal, @ clk
	PSA = 0;		// prescaler given to the TMR0 module
	// configure the prescaler to 101 i.e. 1:64 rate
	T0PS2 = 1;
	T0PS1 = 0;
	T0PS0 = 1;

	// configure the interrupts
	GIE = 1;	// activate interrupts
	TMR0IE = 1;	// activate TMR0 interrupts
	
}
