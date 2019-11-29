/* --------------------------------------------------------------- */
/* ------- DEMO CODE --- BLINKING THE LEDS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --- (c) 2011 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* -------- this is the init file. to be used with: -------------- */
/* --------- "main_LEDBlink_HiTechC.c" --------------------------- */
/* --------------------------------------------------------------- */

// --- specify the processor used
#include <htc.h>

#include "init_LEDBlink_HiTechC.h"

// --- init the PIC18F device
void initMyPIC18F(void)
{
	// PORTA digital
	ADCON1 = 0x0F ;
	ADCON0 = 0;

	// set all ports as OUTPUTS
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x00;

	// set port by port on "all zeros"
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;

}
// make sure to have an empty LAST line in any *.c file (just hit an Enter)!
