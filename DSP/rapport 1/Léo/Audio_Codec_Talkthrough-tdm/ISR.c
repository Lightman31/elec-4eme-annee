///////////////////////////////////////////////////////////////////////////////
//
// 	
//  Experiment 7.2 Talk-through program using BF533 EZ-KIT
//  FILE name: ISR.c
//
//  Description: C file containing the interrupt service routine for SPORT0_RX.
//		 This ISR is executed after a complete frame of input data 	
//		 has been received. The new samples are stored in 			
//		 iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		
//		 iChannel1RightIn respectively.  Then the function 			
//		 Process_Data() is called in which user code can be executed.
//		 After that the processed values are copied from the 		
//		 variables iChannel0LeftOut, iChannel0RightOut, 				//
//		 iChannel1LeftOut and iChannel1RightOut into the dma 		
//		 transmit buffer.	
//  
//  For the book "Embedded Signal Processing with the Micro Signal Architecture"
//		  By Woon-Seng Gan and Sen M. Kuo
//		  Publisher: John Wiley and Sons, Inc.
//
//  Tools used: VisualDSP++ v4.0 (running on BF533 EZ-KIT)
//
///////////////////////////////////////////////////////////////////////////////

#include "Talkthrough.h"


EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	// copy input data from dma input buffer into variables
	iChannel0LeftIn = iRxBuffer1[INTERNAL_ADC_L0];
	iChannel0RightIn = iRxBuffer1[INTERNAL_ADC_R0];
	iChannel1LeftIn = iRxBuffer1[INTERNAL_ADC_L1];
	iChannel1RightIn = iRxBuffer1[INTERNAL_ADC_R1];

	// call function that contains user code
	Process_Data();				

	// copy processed data from variables into dma output buffer
	iTxBuffer1[INTERNAL_DAC_L0] = iChannel0LeftOut;
	iTxBuffer1[INTERNAL_DAC_R0] = iChannel0RightOut;
	iTxBuffer1[INTERNAL_DAC_L1] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_R1] = iChannel1RightOut;
	
	//iTxBuffer1[INTERNAL_DAC_L2] = iChannel1LeftOut;	
	//iTxBuffer1[INTERNAL_DAC_R2] = iChannel1RightOut;
	
	iTxBuffer1[INTERNAL_DAC_L2] = iChannel2LeftOut;
	iTxBuffer1[INTERNAL_DAC_R2] = iChannel2RightOut;
}


