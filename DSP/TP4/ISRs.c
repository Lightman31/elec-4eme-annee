#include "BF533 Flags.h"

//--------------------------------------------------------------------------//
// Function:	Timer0_ISR													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This ISR is executed every time Timer0 expires.				//
//				The old LED pattern is shifted by one; the direction		//
//				depends on the state of sLight_Move_Direction, which is		//
//				changed in FlagA_ISR.										//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Timer0_ISR)
{
	static unsigned char ucActive_LED = 0x01;

	// confirm interrupt handling
	*pTIMER_STATUS = 0x0001;

	// shift old LED pattern by one
	
	if(sLight_Move_Direction)
	{
		if((ucActive_LED = ucActive_LED >> 1) == 0x00) ucActive_LED = 0x20;
	}
	else
	{
		if((ucActive_LED = ucActive_LED << 1) == 0x40) ucActive_LED = 0x01;
	}
	
//--------------------------------------------------------------------------//
// comment the previous "if"
// uncomment the next line if you want to update the leds only by pushbutton
//ucActive_LED = sCoutButtonPress;
//--------------------------------------------------------------------------//

	// write new LED pattern to Port B
	*pFlashA_PortB_Data = ucActive_LED;
}

//--------------------------------------------------------------------------//
// Function:	FlagA_ISR													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This ISR is called every time the button connected to PF8	//
//				is pressed.													//
//				The state of flag sLight_Move_Direction is changed, so the	//
//				shift-direction for the LED pattern in Timer0_ISR changes.	//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(FlagA_ISR)
{
// --- confirm interrupt handling
	*pFIO_FLAG_C = 0x0100; 
// 0x0100 = 0000 0001 0000 0000
// Note: write 1 to clear!

// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//		FIO_ANOM_0311_FLAG_W(0x0100,pFIO_FLAG_C); //workaround for anomaly 05000311
	
   
	
// --- toggle direction of moving light
// --- comment if you want manual increment
	sLight_Move_Direction = ~sLight_Move_Direction;
	
// ------------------------------------------------------------------------ //
// uncomment the next lines if you want to update the leds only by pushbutton
	
/*	
	sCoutButtonPress++;
   if (sCoutButtonPress==0x40)
   {
   		sCoutButtonPress=0;
   }
   */
   
}

