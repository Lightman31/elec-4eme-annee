
/****************************************************************************
 Copyright (c) 2000 Analog Devices Inc. All rights reserved.
 ***************************************************************************
  File Name      : fir_test.c
  Description    : This module tests the fir function.

***************************************************************************/

/* Includes */
#include "mds_def.h"
#include "filter.h"
#include "fir_coeff.h"
#include "fir_input.h"

/* Constants */
#define DELAY_SIZE       BASE_TAPLENGTH

fract16 delay[DELAY_SIZE];
fract16 OUT[BUFFER_SIZE];

void main()
{
	int	i,
		nsamples,
		tapLength;

    fir_state_fr16 s;

    nsamples = BUFFER_SIZE;
    tapLength = BASE_TAPLENGTH ;
     
	fir_init(s, h, delay, tapLength);
	        
	_fir(IN, OUT, nsamples, &s);

}

