///////////////////////////////////////////////////////////////////////////////
//
// 	
//  Experiment 7.1 Talk-through program using BF533 EZ-KIT
//  FILE name: Process_data.c
//
//  Description: C file for processing incoming data.
//		 This function is called from inside the SPORT0 ISR every 
//		 time a complete audio frame has been received. The new 		
//		 input samples can be found in the variables iChannel0LeftIn,
//		 iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		
//		 respectively. The processed	data should be stored in 		
//		 iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		
//		 iChannel1RightOut, iChannel2LeftOut and iChannel2RightOut	
//		 respectively.				 
//  
//  For the book "Embedded Signal Processing with the Micro Signal Architecture"
//		  By Woon-Seng Gan and Sen M. Kuo
//		  Publisher: John Wiley and Sons, Inc.
//
//  Tools used: VisualDSP++ v4.0 (running on BF533 EZ-KIT)
//
///////////////////////////////////////////////////////////////////////////////

#include "Talkthrough.h"


void Process_Data(void)
{
	iChannel0LeftOut = iChannel0LeftIn;
	iChannel0RightOut = iChannel0RightIn;
	
	iChannel1LeftOut = iChannel1LeftIn;
	iChannel1RightOut = iChannel1RightIn;
	
	iChannel2LeftOut = iChannel0LeftIn;
	iChannel2RightOut = iChannel0RightIn;
}
