#include "Talkthrough.h"
#include "BF533 Flags.h"


extern fract16 coef_passebas[TAPS] = {
	#include "coef32.dat" // Pass-bas faible pour PF8
};

extern fract16 coef_passehaut[TAPS] = {
	#include "coef32_highpass.dat" // Pass-haut pour PF10 
};
extern fract16 coef_lowpass1[TAPS] = {
	#include "coef32_lowpass1.dat" // Pass-bas fort pour PF9 
};



//--------------------------------------------------------------------------//
// Function:	Sport0_RX_ISR												//
//																			//
// Description: This ISR is executed after a complete frame of input data 	//
//				has been received. The new samples are stored in 			//
//				iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		//
//				iChannel1RightIn respectively.  Then the function 			//
//				Process_Data() is called in which user code can be executed.//
//				After that the processed values are copied from the 		//
//				variables iChannel0LeftOut, iChannel0RightOut, 				//
//				iChannel1LeftOut and iChannel1RightOut into the dma 		//
//				transmit buffer.											//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{

	static int index = 0;
	
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	
	// call function that contains user code
	if (index == 0)
	{
		Process_Data();
	}				

	sChannel0RightIn[index] = sRxBuffer[INTERNAL_ADC_R0];
	sChannel0LeftIn[index] = sRxBuffer[INTERNAL_ADC_L0];
	

	// copy processed data from variables into dma output buffer
	sTxBuffer[INTERNAL_DAC_L0] = sChannel0LeftOut[index];
	sTxBuffer[INTERNAL_DAC_R0] = sChannel0RightOut[index];

	
	//increment the array index and wait for the next sample to arrive
	index = circindex(index, 1, BUFFER_SIZE);
}


EX_INTERRUPT_HANDLER(FlagA_ISR)
{
// --- confirm interrupt handling
	*pFIO_FLAG_C = 0x0100; 
// 0x0100 = 0000 0001 0000 0000
// Note: write 1 to clear!

// --- if the previous instruction shows an anomaly
// --- it is fixed by the following instruction:
//		FIO_ANOM_0311_FLAG_W(0x0100,pFIO_FLAG_C); //workaround for anomaly 05000311
	
   
	int i;
	

	if (sCoutButtonPress==0x1)   {
		sCoutButtonPress=0x0;
		*pFlashA_PortB_Data = 0x01;
		for(i=0;i<TAPS;i++){
		coef[i]=coef_passebas[i];
		}
		fir_init(stateR, coef, delayR, TAPS, 1);
		fir_init(stateL, coef, delayL, TAPS, 1);
   }
	else if(sCoutButtonPress==0x0){
	 	sCoutButtonPress=0x1;
	 	*pFlashA_PortB_Data = 0x00;
		for(i=0;i<TAPS;i++){
		coef[i]=coef_passehaut[i];
		}
	    fir_init(stateR, coef, delayR, TAPS, 1);
		fir_init(stateL, coef, delayL, TAPS, 1);
	}
	

	
	
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

