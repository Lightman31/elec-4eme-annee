#include <p18F4550.inc>
    ORG 0x0000  ;  processor  r e s e t  vector
    GOTO prog_init  ;  go  to  beginning  of  program
    ORG 0x0008
    GOTO irq_handle
    
    MAIN_PROG CODE ;  l e t  l i n k e r  place  main program
    
    irq_handle
	BTFSC INTCON, TMR0IF
	GOTO TMR0_interrupt
	RETFIE
	
    TMR0_interrupt ; --- TMR0 interrupt service routine
	bcf INTCON, TMR0IF
	incf PORTD
	retfie ; return from interrupt
    
	
    prog_init
	bsf T0CON, TMR0ON ; TIMER0 is ON
	bsf T0CON, T08BIT ; TIMER0 on 8 bits
	bcf T0CON, T0CS ; internal clock source
	bcf T0CON, PSA ; give the prescaler to TMR0
	clrf TRISD ; PORTD is output
	clrf PORTD ; clear PORTD
	btfsc RBIE, TMR0
	bsf INTCON, GIE ; activate interrupts
	bsf INTCON, RBIE ; activate TMR0 interrupt
	clrf TMR0 ; clear the timer
    goto MAIN_LOOP
	
    MAIN_LOOP
	; --- wait for an interrupt
	goto MAIN_LOOP
	
end
