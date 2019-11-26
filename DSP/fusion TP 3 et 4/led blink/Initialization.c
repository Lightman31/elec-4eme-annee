#include "BF533 Flags.h"
#include "Talkthrough.h"


//--------------------------------------------------------------------------//
// Function:	Init_EBIU													//
//																			//
// Description:	This function initializes and enables asynchronous memory 	//
//				banks in External Bus Interface Unit so that Flash A can be //
//				accessed.													//
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
// Description:	This function initializes pin direction of Port A in Flash A//
//				to output.  The AD1836_RESET on the ADSP-BF533 EZ-KIT board //
//				is connected to Port A.										//
//--------------------------------------------------------------------------//
void Init_Flash(void)
{
	*pFlashA_PortA_Dir = 0x1;
	
		*pFlashA_PortB_Dir = 0x3f;
// --- Explanation: Direction register controls IO pins direction.
// --- This is a 8-bit read-write register. When a bit is 0, 
// --- a corresponding pin functions as an input.  When the bit is 1,
// --- a corresponding pin is an output.
}

//--------------------------------------------------------------------------//
// Function:	Init_FIR													//
//																			//
// Description:	This function initializes FIR filter states for right & left//
//				channels													//
//--------------------------------------------------------------------------//
void Init_FIR(void)
{
	fir_init(stateR, coef, delayR, TAPS, 1);
	fir_init(stateL, coef, delayL, TAPS, 1);
}


//--------------------------------------------------------------------------//
// Function:	Init1836()													//
//																			//
// Description:	This function sets up the SPI port to configure the AD1836. //
//				The content of the array sCodec1836TxRegs is sent to the 	//
//				codec.														//
//--------------------------------------------------------------------------//
void Init1836(void)
{
	int i;
	int j;
	static unsigned char ucActive_LED = 0x01;
	
	// write to Port A to reset AD1836
	*pFlashA_PortA_Data = 0x00;
	
	// write to Port A to enable AD1836
	*pFlashA_PortA_Data = ucActive_LED;
	
	// wait to recover from reset
	for (i=0; i<0xf0000; i++) asm("nop;");

	// Enable PF4
	*pSPI_FLG = FLS4;
	// Set baud rate SCK = HCLK/(2*SPIBAUD) SCK = 2MHz	
	*pSPI_BAUD = 16;
	// configure spi port
	// SPI DMA write, 16-bit data, MSB first, SPI Master
	*pSPI_CTL = TIMOD_DMA_TX | SIZE | MSTR;
	
	// Set up DMA5 to transmit
	// Map DMA5 to SPI
	*pDMA5_PERIPHERAL_MAP	= 0x5000;
	
	// Configure DMA5
	// 16-bit transfers
	*pDMA5_CONFIG = WDSIZE_16;
	// Start address of data buffer
	*pDMA5_START_ADDR = (void *)sCodec1836TxRegs;
	// DMA inner loop count
	*pDMA5_X_COUNT = CODEC_1836_REGS_LENGTH;
	// Inner loop address increment
	*pDMA5_X_MODIFY = 2;
	
	// enable DMAs
	*pDMA5_CONFIG = (*pDMA5_CONFIG | DMAEN);
	// enable spi
	*pSPI_CTL = (*pSPI_CTL | SPE);
	
	// wait until dma transfers for spi are finished 
	for (j=0; j<0xaff0; j++) asm("nop;");
	
	// disable spi
	*pSPI_CTL = 0x0000;
}


//--------------------------------------------------------------------------//
// Function:	Init_Sport0													//
//																			//
// Description:	Configure Sport0 for I2S mode, to transmit/receive data 	//
//				to/from the AD1836. Configure Sport for external clocks and //
//				frame syncs.												//
//--------------------------------------------------------------------------//
void Init_Sport0(void)
{
	// Sport0 receive configuration
	// External CLK, External Frame sync, MSB first, Active Low
	// 16-bit data, Stereo frame sync enable
	*pSPORT0_RCR1 = RFSR | RCKFE | LRFS;
	*pSPORT0_RCR2 = RSFSE | SLEN_16;
	
	// Sport0 transmit configuration
	// External CLK, External Frame sync, MSB first, Active Low
	// 16-bit data, Secondary side enable, Stereo frame sync enable
	*pSPORT0_TCR1 = TCKFE | TFSR | LTFS;
	*pSPORT0_TCR2 = TSFSE | SLEN_16;
	
}


//--------------------------------------------------------------------------//
// Function:	Init_DMA													//
//																			//
// Description:	Initialize DMA1 in autobuffer mode to receive and DMA2 in	//
//				autobuffer mode to transmit									//
//--------------------------------------------------------------------------//
void Init_DMA(void)
{
	// Set up DMA1 to receive
	// Map DMA1 to Sport0 RX
	*pDMA1_PERIPHERAL_MAP = 0x1000;
	
	// Configure DMA1
	// 16-bit transfers, Interrupt on completion, Autobuffer mode
	*pDMA1_CONFIG = WNR | WDSIZE_16 | DI_EN | FLOW_1;
	// Start address of data buffer
	*pDMA1_START_ADDR = (void *)sRxBuffer;
	// DMA inner loop count
	*pDMA1_X_COUNT = 2;
	// Inner loop address increment
	*pDMA1_X_MODIFY = 2;
	
	
		
	// Set up DMA2 to transmit
	// Map DMA2 to Sport0 TX
	*pDMA2_PERIPHERAL_MAP = 0x2000;
	
	// Configure DMA2
	// 16-bit transfers, Autobuffer mode
	*pDMA2_CONFIG = WDSIZE_16 | FLOW_1;
	// Start address of data buffer
	*pDMA2_START_ADDR = (void *)sTxBuffer;
	// DMA inner loop count
	*pDMA2_X_COUNT = 2;
	// Inner loop address increment
	*pDMA2_X_MODIFY = 2;
}

//--------------------------------------------------------------------------//
// Function:	Enable_DMA_Sport											//
//																			//
// Description:	Enable DMA1, DMA2, Sport0 TX and Sport0 RX					//
//--------------------------------------------------------------------------//
void Enable_DMA_Sport0(void)
{
	// enable DMAs
	*pDMA2_CONFIG	= (*pDMA2_CONFIG | DMAEN);
	*pDMA1_CONFIG	= (*pDMA1_CONFIG | DMAEN);
	
	// enable Sport0 TX and RX
	*pSPORT0_TCR1 	= (*pSPORT0_TCR1 | TSPEN);
	*pSPORT0_RCR1 	= (*pSPORT0_RCR1 | RSPEN);
}

//--------------------------------------------------------------------------//
// Function:	Init_Interrupts												//
//																			//
// Description:	Initialize Interrupt for Sport0 RX							//
//--------------------------------------------------------------------------//
void Init_Interrupts(void)
{
	// Set Sport0 RX (DMA1) interrupt priority to 2 = IVG9 
	*pSIC_IAR0 = 0xffffffff;
	*pSIC_IAR1 = 0xffffff2f;
	*pSIC_IAR2 = 0xffff5ff4;// Timer0 -> ID4; FlagA -> ID5
// --- Explanation: 0xffff5ff4 = 1111 1111 1111 1111 0101 1111 1111 0100
// --- i.e. activate Timer0 + PFA (FlagA) interrupts
// --- PFA gets 0101 i.e. IVG 12 and Timer 0 gets IVG 11.
// --- Confused? See the Lab. 4 - "how it works" for more information

	// assign ISRs to interrupt vectors
	// Sport0 RX ISR -> IVG 9
	register_handler(ik_ivg9, Sport0_RX_ISR);
// --- assign ISRs to interrupt vectors ---
	register_handler(ik_ivg11, Timer0_ISR);		// Timer0 ISR -> IVG 11
	register_handler(ik_ivg12, FlagA_ISR);		// FlagA ISR -> IVG 12

	// enable Sport0 RX interrupt
	*pSIC_IMASK = 0x00000200;
						



	// enable Timer0 and FlagA interrupt
	//*pSIC_IMASK = 0x00090000;
// --- Explanation: Unmasking of the interrupts
// --- by setting corresponding bits in SIC_IMASK register

}




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



