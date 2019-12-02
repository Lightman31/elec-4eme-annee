/* --------------------------------------------------------------- */
/* -------- DEMO CODE --- SEVEN SEGMENT CLOCK -------------------- */
/* ---------------------- USING INTERRUPTS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --- (c) 2014 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* -------- this is the hearder file. to be used with: ----------- */
/* --- "SevenSeg_PIC16F.c", "SevenSeg_PIC16F.h" ------------------ */
/* -------------and "SevenSeg_Functions.c" ----------------------- */
/* --------------------------------------------------------------- */
#ifndef	FUNCTIONS_SEVENSEG_HITECH
#define	FUNCTIONS_SEVENSEG_HITECH

#define _XTAL_FREQ 8000000 // oscillator frequency for _delay_ms()

// --- the compulsory header file for HI-TECH C ---------------------
#include <htc.h>

#include "SevenSeg_PIC18F.h"


// --- prototype for the DISPLAY routine
void SevenSegDisplay(unsigned char dis[Number7SegDisplays]);

// --- prototype for the APPLY MASK routine
unsigned char SevenSegApplyMask(unsigned char raw);

// --- prototype for the TIME UPDATE routine
unsigned char time_update();


#endif