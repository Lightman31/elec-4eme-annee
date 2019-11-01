///////////////////////////////////////////////////////////////////////////////
//
// 	
//  Experiment 7.2 Talk-through program using BF533 EZ-KIT
//  FILE name: main.c
//
//  Description:	This program sets up the SPI port on the ADSP-BF533 to 
//			configure the AD1836 codec.  The SPI port is disabled 	
//			after initialization.  The data to/from the codec are 
//			transfered over SPORT0 in TDM mode.
//			SPORT0 is then setup to receive/transmit audio samples 
//			from the AD1836.  Audio samples received from the AD1836 
//			are moved into the DSP's receive buffer, using DMA.  
//			The samples are processed by the ADSP-BF533 and place in 
//			the transmit buffer. In turn, the transmit buffer is used 
//			to transmit data to the AD1836.  This results in a simple 
//			talk-through where data is moved in and out of the DSP with out 
//			performing any computations on the data.
//
//  Connections:	Disconnect RSCLK0 and TSCLK0 (Turn SW9 pin 6 OFF)	   
//          Disconnect RFS0 and TFS0 (Turn SW9 pin 5 OFF)		   
//          Connect an input source (such as a sound card) to the Audio	
//			input jack and an output source (such as headphones) to 
//			the Audio output jack									
//																			
//													
//  
//  For the book "Embedded Signal Processing with the Micro Signal Architecture"
//		  By Woon-Seng Gan and Sen M. Kuo
//		  Publisher: John Wiley and Sons, Inc.
//
//  Tools used: VisualDSP++ v4.0 (running on BF533 EZ-KIT)
//
//  (C) Copyright 2003 - Analog Devices, Inc.  All rights reserved.	
//
///////////////////////////////////////////////////////////////////////////////

#include "Talkthrough.h"
#include "sysreg.h"
#include "ccblkfn.h"

//--------------------------------------------------------------------------//
// Variables																//
//																			//
// Description:	The variables iChannelxLeftIn and iChannelxRightIn contain 	//
//				the data coming from the codec AD1836.  The (processed)		//
//				playback data are written into the variables 				//
//				iChannelxLeftOut and iChannelxRightOut respectively, which 	//
//				are then sent back to the codec in the SPORT0 ISR.  		//
//				The values in the array iCodec1836TxRegs can be modified to //
//				set up the codec in different configurations according to   //
//				the AD1885 data sheet.										//
//--------------------------------------------------------------------------//
// left input data from ad1836
int iChannel0LeftIn, iChannel1LeftIn;
// right input data from ad1836
int iChannel0RightIn, iChannel1RightIn;
// left ouput data for ad1836	
int iChannel0LeftOut, iChannel1LeftOut, iChannel2LeftOut;
// right ouput data for ad1836
int iChannel0RightOut, iChannel1RightOut,iChannel2RightOut;
// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{									
					DAC_CONTROL_1	| 0x000,
					DAC_CONTROL_2	| 0x000,
					DAC_VOLUME_0	| 0x3ff,
					DAC_VOLUME_1	| 0x3ff,
					DAC_VOLUME_2	| 0x3ff,
					DAC_VOLUME_3	| 0x3ff,
					DAC_VOLUME_4	| 0x3ff,
					DAC_VOLUME_5	| 0x3ff,
					ADC_CONTROL_1	| 0x000,
					ADC_CONTROL_2	| 0x180,
					ADC_CONTROL_3	| 0x000
					
};
// SPORT0 DMA transmit buffer
volatile int iTxBuffer1[8];
// SPORT0 DMA receive buffer
volatile int iRxBuffer1[8];


//--------------------------------------------------------------------------//
// Function:	main														//
//																			//
// Description:	After calling a few initalization routines, main() just 	//
//				waits in a loop forever.  The code to process the incoming  //
//				data can be placed in the function Process_Data() in the 	//
//				file "Process_Data.c".										//
//--------------------------------------------------------------------------//
void main(void)
{

	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_EBIU();
	Init_Flash();
	Init1836();
	Init_Sport0();
	Init_DMA();
	Init_Sport_Interrupts();
	Enable_DMA_Sport0();
	
	while(1);
}
