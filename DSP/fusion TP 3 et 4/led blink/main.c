/*****************************************************************************
**																			**
**	 Name: 	FIO pins, Interrupts, and Timer in C							**
**																			**
******************************************************************************

(C) Copyright 2006 - Analog Devices, Inc.  All rights reserved.

2013 modifications, supplementary comments  - Stefan Ataman

Project Name:	BF533 Flags C

Date Modified:	3/31/03		Ver 1.01

Software:		VisualDSP++ 4.5

Hardware:		ADSP-BF533 EZ-KIT Lite

Connections:	Switch SW9_1 has to be turned on in order to connect SW7 to PF8

Purpose:		To demonstrate the configuration of FIO pins, Timer, and
				Interrupts in C

*****************************************************************************/

#include "BF533 Flags.h"
#include "ccblkfn.h"
#include "sysreg.h"
#include "Talkthrough.h"
#include "sysreg.h"

//--------------------------------------------------------------------------//
// Variables																//
//--------------------------------------------------------------------------//
// flag indicating direction of moving light (toggled in FlagA ISR)
short sLight_Move_Direction = 0;

short sCoutButtonPress = 0;





//--------------------------------------------------------------------------//
// Variables																//
//																			//
// Description:	The variables sChannelxLeftIn and sChannelxRightIn contain 	//
//				the data coming from the codec AD1836.  The (processed)		//
//				playback data are written into the variables 				//
//				sChannelxLeftOut and sChannelxRightOut respectively, which 	//
//				are then sent back to the codec in the SPORT0 ISR.  		//
//				The values in the array iCodec1836TxRegs can be modified to //
//				set up the codec in different configurations according to   //
//				the AD1836 data sheet.										//
//--------------------------------------------------------------------------//
// left input data from ad1836
short sChannel0LeftIn[BUFFER_SIZE];
// right input data from ad1836
short sChannel0RightIn[BUFFER_SIZE];

// left output data for ad1836	
short sChannel0LeftOut[BUFFER_SIZE];
// right output data for ad1836
short sChannel0RightOut[BUFFER_SIZE];



// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{									
					DAC_CONTROL_1	| 0x010, // 16bit data width DAC 
					DAC_CONTROL_2	| 0x000,
					DAC_VOLUME_0	| 0x3ff,
					DAC_VOLUME_1	| 0x3ff,
					DAC_VOLUME_2	| 0x3ff,
					DAC_VOLUME_3	| 0x3ff,
					DAC_VOLUME_4	| 0x000,
					DAC_VOLUME_5	| 0x000,
					ADC_CONTROL_1	| 0x000,
					ADC_CONTROL_2	| 0x020, // 16bit data width ADC
					ADC_CONTROL_3	| 0x000
					
};
// SPORT0 DMA transmit buffer
volatile short sTxBuffer[2];
// SPORT0 DMA receive buffer
volatile short sRxBuffer[2];



fract16 delayL[TAPS]={0};
fract16 delayR[TAPS]={0};

fract16 coef[TAPS] = {
	// low-pass
	// #include "coef32_low2_158taps.dat"
	#include "coef32.dat"
	// high-pass filter with Fstop=3000 and Fpass=3500
	// #include "fdacoefs_high4_032taps.dat"
	// band pas-pass filters
	// #include "fdacoefs_pass4_341taps.dat"
	// #include "fdacoefs_pass4_032taps.dat"
	// band-stop
	// #include "fdacoefs_stop4_162taps.dat"
	
	
};


fir_state_fr16 stateL;
fir_state_fr16 stateR;




//--------------------------------------------------------------------------//
// Function:	main														//
//--------------------------------------------------------------------------//
void main(void)
{

	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_EBIU();
	Init_Flash();
	Init1836();
	Init_Sport0();

	Init_FIR();
	
	Init_DMA()
	
	
	
	Init_Flags();
	Init_Timers();
	Init_Interrupts();
	Enable_DMA_Sport0();

	while(1);
}

