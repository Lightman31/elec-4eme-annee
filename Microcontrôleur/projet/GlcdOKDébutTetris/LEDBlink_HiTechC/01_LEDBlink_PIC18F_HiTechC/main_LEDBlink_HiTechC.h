/* --------------------------------------------------------------- */
/* ------- DEMO CODE --- BLINKING THE LEDS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --- (c) 2015 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* -------- this is the init file. to be used with: -------------- */
/* --------- "init_LEDBlink_C18.c" ------------------------------- */
/* --------------------------------------------------------------- */

#ifndef	MAIN_LED_BLINK_HITECH
#define	MAIN_LED_BLINK_HITECH

#define XTAL_FREQ 8000000 // oscillator frequency for _delay()

#define _XTAL_FREQ 8000000 // oscillator frequency for _delay_ms()

// --- the compulsory header file for HI-TECH C
#include <htc.h>



// declare the function prototypes

// inits the PIC18F device
void PIC18F_allLEDs_STATE_ONE(void);

void PIC18F_allLEDs_STATE_TWO(void);


#endif