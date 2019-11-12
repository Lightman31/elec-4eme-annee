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

//--------------------------------------------------------------------------//
// Variables																//
//--------------------------------------------------------------------------//
// flag indicating direction of moving light (toggled in FlagA ISR)
short sLight_Move_Direction = 0;

short sCoutButtonPress = 0;

//--------------------------------------------------------------------------//
// Function:	main														//
//--------------------------------------------------------------------------//
void main(void)
{

	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_Flags();
	Init_Timers();
	Init_EBIU();
	Init_Flash();
	Init_Interrupts();

	while(1);
}

