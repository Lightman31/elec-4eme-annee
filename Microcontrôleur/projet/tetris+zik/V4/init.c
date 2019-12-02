#include "init.h"

// --- init the PIC18F device
void initMyPIC18F(void)
{
	// PORTA digital
	ADCON1 = 0x0F ;
	ADCON0 = 0;

	// set all ports as OUTPUTS and port A as input 
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0xFF;

	// set port by port on "all zeros"
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
// make sure to have an empty LAST line in any *.c file (just hit an Enter)!


}
// make sure to have an empty LAST line in any *.c file (just hit an Enter)!

