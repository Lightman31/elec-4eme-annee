/* --------------------------------------------------------------- */
/* -------- DEMO CODE --- SEVEN SEGMENT CLOCK -------------------- */
/* ---------------------- USING INTERRUPTS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --- (c) 2014 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* -------- this is the hearder file. to be used with: ----------- */
/* -------------- "SevenSeg_PIC16F.c" ---------------------------- */
/* --------------------------------------------------------------- */
#ifndef	MAIN_SEVENSEG_HITECH
#define	MAIN_SEVENSEG_HITECH

#define _XTAL_FREQ 8000000 // oscillator frequency for _delay_ms()

// --- the compulsory header file for HI-TECH C ---------------------
#include <htc.h>

/* --------------------------------------------------------------- */
/* --- describe where the SevenSeg display is connected ---------- */
/* --------------------------------------------------------------- */

// --- how many SevenSegment displays? ------------------------------
// --- note: the easyPIC 4 and 5 boards have 4 ----------------------
#define Number7SegDisplays	4

// --- how much delay you want per segment?
#define delay_per_segment_ms 1

// --- control bits are on PORTA ------------------------------------
#define	Enable_dis0	RA0
#define	Enable_dis1	RA1
#define	Enable_dis2	RA2
#define	Enable_dis3	RA3

// --- data comes on PORTD ------------------------------------------
#define	Data_display	PORTD

/* --------------------------------------------------------------- */
/* --- TMR0 timers gives the second and uses a counter ----------- */
/* --------------------------------------------------------------- */

// --- for counting the second
#define count1_start_value 123	// the value of the counter1
								// variable in order to have
								// the delay closest to 1s


/* --------------------------------------------------------------- */
/* ------------------ declare the VARIABLES ---------------------- */
/* --------------------------------------------------------------- */

// --- declare the counter variable ---------------------------------
short count1=count1_start_value;

unsigned char sec0, sec1, min0, min1, hour0, hour1;

bit	update_time=0;
// --- display mm:ss or hh:mm ?
// mmss=0 => display hhmm
unsigned char mmss=1;

// --- declare the dis_data as an array (dis0_data, dis1_data...)
unsigned char dis_data[Number7SegDisplays];

// --- declare the dis_raw as an array (dis0_raw, dis1_raw...)
unsigned char raw_data[Number7SegDisplays];

/* --------------------------------------------------------------- */
/* ------------- declare the function prototypes ----------------- */
/* --------------------------------------------------------------- */


// --- prototypes of the used functions in the main file ---

// --- prototype for the PIC INITIALIZATION function ---
void initMyPIC18F(void);


// --- prototype for the DISPLAY routine
void SevenSegDisplay(unsigned char dis[Number7SegDisplays]);

// --- prototype for the APPLY MASK routine
unsigned char SevenSegApplyMask(unsigned char raw);

// --- prototype for the TIME UPDATE routine
unsigned char time_update();


#endif