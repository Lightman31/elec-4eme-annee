/* --------------------------------------------------------------- */
/* ------ DEMO CODE --- BLINKING AROUND LEDS on a PIC18F4550 ----- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --------------------------------------------------------------- */
/* --- (c) 2015 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* --- PORTA is incremented using PORTA++ ------------------------ */
/* --- PORTB is incremented using the variable PORT_variable ----- */
/* --- PORTC is blinked - ON and OFF ----------------------------- */
/* --- PORTD is partially blinked - just RD2, RD4 and RD7 -------- */
/* --- PORTE is incremented using assembler commands ------------- */
/* --------------------------------------------------------------- */
/* --- uses the __delay_ms() function from the HI-TECH library --- */
/* --- in the header file the following line is needed: ---------- */
/* --- #define _XTAL_FREQ 8000000 -------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */


// --- the compulsory header file for HI-TECH C
#include <htc.h>

// config line
#pragma config WDT = OFF
#pragma config LVP = OFF  //low voltage programming off 
//#pragma config OSC = HS
#pragma config FOSC = HS  // HS oscillator, HS used by USB

// the include (header) file with function prototypes
#include "main_LEDBlink_HiTechC.h"

#include "init_LEDBlink_HiTechC.h" 


// prototypes of the used functions in the main file declared again
void initMyPIC18F(void);


// --- declare a variable
int PORT_variable=0;

/* --------------------------------------------------------------- */
/* -------------- the main function ------------------------------ */
/* --------------------------------------------------------------- */
void main (void)
{
	// call the function that will init the PIC
	initMyPIC18F();

  	// the infinite loop
	// remember: any program should be "kept" in an infinite loop
	// you have no OS, therefore no return(0)
 	while (1)
  	{
		// --- set all ports on STATE ONE
		// --- see below details
		PIC18F_allLEDs_STATE_ONE();
				
		// --- Delay, so human eye can see change
		__delay_ms(60);
				
	
		// --- set all ports on STATE TWO
		// --- see below details
		PIC18F_allLEDs_STATE_TWO();

		// --- Delay again
		__delay_ms(60);
		

    } 		// end the infinite while loop
} 			// end of the main function

/* --------------------------------------------------------------- */
/* ----------- now state the functions called earlier ------------*/
/* --------------------------------------------------------------- */

/* --------------------------------------------------------------- */
/* ------------ set all ports on STATE ONE ----------------------- */
/* --------------------------------------------------------------- */
/* ---- STATE ONE means: ----------------------------------------- */
/* --- PORTA is incremented using PORTA++ ------------------------ */
/* --- PORTB is incremented using the variable PORT_variable ----- */
/* --- PORTC is blinked - ON and OFF ----------------------------- */
/* --- PORTD is partially blinked - just RD2, RD4 and RD7 -------- */
/* --- PORTE is incremented using assembler commands ------------- */
/* --------------------------------------------------------------- */
void PIC18F_allLEDs_STATE_ONE(void)
{
	PORTA++;				// increment a port using ++
	PORT_variable++;		// increment a variable
	PORTB = PORT_variable;	// PortB <= variable
	PORTC = 0xFF;			// PORTC = "all ones"

	// individually touch PORTD bits
	PORTDbits.RD2 = 1;
	PORTDbits.RD4 = 1;
	PORTDbits.RD7 = 1;	
	// increment PORTE in assembler
	asm("INCF PORTE");
}
/* --------------------------------------------------------------- */
/* ------------ set all ports on STATE TWO ----------------------- */
/* --------------------------------------------------------------- */
/* STATE TWO means: ---------------------------------------------- */
/* --- PORTA is unchanged ---------------------------------------- */
/* --- PORTB is unchanged ---------------------------------------- */
/* --- PORTC is CLEARED ------------------------------------------ */
/* --- PORTD is CLEARED ------------------------------------------ */
/* --- PORTE is unchanged ---------------------------------------- */
/* --------------------------------------------------------------- */
void PIC18F_allLEDs_STATE_TWO(void)
{
	//	--- PORTA stays unchanged - all LEDs keep their state
	//	--- PORTB stays unchanged - all LEDs keep their state
	PORTC = 0x00;		// PORTC is CLEARED - all LEDs turned OFF
	PORTD = 0x00;		// PORTD is CLEARED - all LEDs turned OFF
	//	--- PORTE stays unchanged - all LEDs keep their state
	//PORTE=0x00;
}

