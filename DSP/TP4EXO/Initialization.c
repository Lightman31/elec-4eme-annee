#include "BF533 Flags.h"

//--------------------------------------------------------------------------//
// Function:	Init_Flags													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function configures PF8 as input for edge sensitive	//
//				interrupt generation.										//
//				The switch connected to PF8 (SW7) can be used to change the	//
//				direction of the moving light.								//
//--------------------------------------------------------------------------//
void Init_Flags(void)
{
	
// ------------------------------------------------------------------------ //
// --- this value programs the PF8 pin ---
	*pFIO_INEN		= 0x0100;
// --- Explanation:  *pFIO_INEN =  0x0100  i.e.  0000 0001 0000 0000
// --- set a 1 to enable FLAG input
// --- see the Lab. 4 - how it works for more information

	
// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//		FIO_ANOM_0311_INEN_W(0x0100);// workaround for anomaly 05000311.
	
// ------------------------------------------------------------------------ //
// --- This reset value makes all pins as inputs ---
	*pFIO_DIR		= 0x0000;
// --- Explanation: A logic 0 configures a PFx pin as an input
	
// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//	FIO_ANOM_0311_DIR_W(0x0000);
//For more information please refer to the comment header in file sys/05000311.h
	
// ------------------------------------------------------------------------ //
// --- This value sets PF8 pin to be EDGE sensitive ---
	*pFIO_EDGE		= 0x0100;
// --- Explanation:  FIO_EDGE Flag Interrupt Sensitivity Register
// --- 0 -> Level Sensitive / 1 -> EDGE Sensitive

	
// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//		FIO_ANOM_0311_EDGE_W(0x0100);
	
// ------------------------------------------------------------------------ //	
// --- This value enables PF8 pin to accept interrupts
	*pFIO_MASKA_D		= 0x0100;
// --- Explanation:  FIO_MASKA_D Register to Enable Interrupt
// --- *pFIO_MASKA_D = 0x0100 i.e. 0000 0001 0000 0000

// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//		FIO_ANOM_0311_MASKA_W(0x0100,pFIO_MASKA_D);
}

//--------------------------------------------------------------------------//
// Function:	Init_Timers													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises Timer0 for PWM mode.				//
//				It is used as reference for the 'shift-clock'.				//
//--------------------------------------------------------------------------//
void Init_Timers(void)
{
	*pTIMER0_CONFIG		= 0x0019;
	*pTIMER0_PERIOD		= 0x00800000;
	*pTIMER0_WIDTH		= 0x00400000;
	*pTIMER_ENABLE		= 0x0001;
}

//--------------------------------------------------------------------------//
// Function:	Init_EBIU													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises and enables the asynchronous		//
//				memory banks for the External Bus Interface Unit (EBIU), so	//
//				that access to Flash A is possible.							//
//--------------------------------------------------------------------------//
void Init_EBIU(void)
{
	*pEBIU_AMBCTL0	= 0x7bb07bb0;
	*pEBIU_AMBCTL1	= 0x7bb07bb0;
	*pEBIU_AMGCTL	= 0x000f;
}

//--------------------------------------------------------------------------//
// Function:	Init_Flash													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function sets the pin direction of Port B in Flash A	//
//				to output.													//
//				The LEDs on the ADSP-BF533 EZ-KIT are connected to Port B.	//
//--------------------------------------------------------------------------//
void Init_Flash(void)
{
	*pFlashA_PortB_Dir = 0x3f;
// --- Explanation: Direction register controls IO pins direction.
// --- This is a 8-bit read-write register. When a bit is 0, 
// --- a corresponding pin functions as an input.  When the bit is 1,
// --- a corresponding pin is an output.
}

//--------------------------------------------------------------------------//
// Function:	Init_Interrupts												//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises the interrupts for Timer0 and		//
//				FlagA (PF8).												//
//--------------------------------------------------------------------------//
void Init_Interrupts(void)
{
// --- assign core IDs to interrupts
	*pSIC_IAR0 = 0xffffffff;
	*pSIC_IAR1 = 0xffffffff;
	*pSIC_IAR2 = 0xffff5ff4;					// Timer0 -> ID4; FlagA -> ID5
// --- Explanation: 0xffff5ff4 = 1111 1111 1111 1111 0101 1111 1111 0100
// --- i.e. activate Timer0 + PFA (FlagA) interrupts
// --- PFA gets 0101 i.e. IVG 12 and Timer 0 gets IVG 11.
// --- Confused? See the Lab. 4 - "how it works" for more information


// --- assign ISRs to interrupt vectors ---
	register_handler(ik_ivg11, Timer0_ISR);		// Timer0 ISR -> IVG 11
	register_handler(ik_ivg12, FlagA_ISR);		// FlagA ISR -> IVG 12

	// enable Timer0 and FlagA interrupt
	*pSIC_IMASK = 0x00090000;
// --- Explanation: Unmasking of the interrupts
// --- by setting corresponding bits in SIC_IMASK register

}

