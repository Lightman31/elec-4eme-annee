/* --------------------------------------------------------------- */
/* -------- DEMO CODE --- SEVEN SEGMENT CLOCK -------------------- */
/* ---------------------- USING INTERRUPTS on a PIC18F4550 ------- */
/* ------------ using Michrochip's HI-TECH C --------------------- */
/* --------------------------------------------------------------- */
/* --- (c) 2014 Stefan Ataman ------------------------------------ */
/* --------------------------------------------------------------- */
/* --- the functions: -------------------------------------------- */
/* --- SevenSegDisplay ------------------------------------------- */
/* --- SevenSegApplyMask ----------------------------------------- */
/* --- time_update ----------------------------------------------- */
/* --------------------------------------------------------------- */

// --- the compulsory header file for HI-TECH C
//#include <htc.h>
#include <htc.h>

// the h-file with the prototypes
#include "SevenSeg_Functions.h"

/* --------------------------------------------------------------- */
/* ------------ the SEVEN SEGMENT DISPLAY function --------------- */
/* --------------------------------------------------------------- */
/* --- ACTION: reads the input vector dis[] and sends it to ------ */
/* --- the corresponding 7-segment display. multiplexing is used - */
/* --- each segment is "blinked" for delay_per_segment_ms -------- */
/* --------------------------------------------------------------- */
void SevenSegDisplay(unsigned char dis[Number7SegDisplays])
{
	// --- display on the FIRST segment (dis0) --------
	// ------------------------------------------------
	// --- put data for dis0 on the  data port --------
	Data_display=dis[0];
	// --- enable (dis0) -------------
	Enable_dis0=1;
	// --- wait ----------------------
	__delay_ms(delay_per_segment_ms);
	// --- disable (dis0) ------------
	Enable_dis0=0;
	// --- done with the fist segment

	// -- now do the same thing with the others segments, you've got the idea

	// display on the SECOND segment
	Enable_dis1=1;
	Data_display=dis[1];
	__delay_ms(delay_per_segment_ms);
	Enable_dis1=0;
	// display on the THIRD segment
	Enable_dis2=1;
	Data_display=dis[2];
	__delay_ms(delay_per_segment_ms);
	Enable_dis2=0;
	// display on the FOURTH segment
	Enable_dis3=1;
	Data_display=dis[3];
	__delay_ms(delay_per_segment_ms);
	Enable_dis3=0;
}

/* --------------------------------------------------------------- */
/* ------------------ the APPLY MASK function -------------------- */
/* --------------------------------------------------------------- */
/* -------------- i.e. conversion from binary to BCD ------------- */
/* --------------------------------------------------------------- */
unsigned char SevenSegApplyMask(unsigned char raw)
{
	unsigned char dis;
	switch (raw)
	{
	case 0 : dis=0x3F; 	// mask for 0
			break;
	case 1 : dis=0x06; 	// mask for 1
			break;
	case 2 : dis=0x5B; 	// mask for 2
			break;
	case 3 : dis=0x4F; 	// mask for 3
			break;
	case 4 : dis=0x66; 	// mask for 4
			break;
	case 5 : dis=0x6D; 	// mask for 5
			break;
	case 6 : dis=0x7D; 	// mask for 6
			break;
	case 7 : dis=0x07; 	// mask for 7
			break;
	case 8 : dis=0x7F; 	// mask for 8
			break;
	case 9 : dis=0x6F; 	// mask for 9
			break;
	default : dis=0x79; 	// mask for E
			break;
	}
	// return the MASK
	return dis;
}

/* --------------------------------------------------------------- */
/* ------------- update the TIME to be displayed ----------------- */
/* --------------------------------------------------------------- */
unsigned char time_update()
{
	// reset the (software) flag
	update_time=0;
	// your display is somthing like: min1 min0 sec1 sec0
	// good. it is time to update it.
	// --- is sec0=10 ? ---
	if (sec0==10)
	{	// yes. well, then...
		sec0=0;
		sec1++;
	}
	// is sec1=6 ?
	if (sec1==6)
	{
		sec1=0;
		min0++;
	}
	if (min0==10)
	{
		min0=0;
		min1++;
	}
	if (min1==6)
	{
		min1=0;
		hour0++;
	}
	if (hour0==10)
	{
		hour0=0;
		hour1++;
	}
	if (hour1=24)
	{
		hour1=0;
	}
	// continue here
	
	// --- update raw data vector ---
	// do you want to display mm:ss?
	// in this DEMO, mmss=0;
	// want to extend the code? read a pushbutton etc. etc.
	if (mmss)
	{ // YES
	raw_data[0]=sec0;
	raw_data[1]=sec1;
	raw_data[2]=min0;
	raw_data[3]=min1;
	}
	else
	{ // NO, hh:mm
	raw_data[0]=min0;
	raw_data[1]=min1;
	raw_data[2]=hour0;
	raw_data[3]=hour1;
	}

	return raw_data;
}