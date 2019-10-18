#include <p18F4550.inc>
ORG 0x0000  ;  processor  r e s e t  vector
GOTO prog_init  ;  go  to  beginning  of  program
ORG 0x0008
GOTO irq_handle

MAIN_PROG CODE ;  l e t  l i n k e r  place  main program

irq_handle  ; ??? i n t e r r u p t r o u ti n e
    ; ??? f l a g t e s t ?> i s i t TMR0?
    btfsc INTCON , RBIF
    goto TMR0_interrupt ; ye s , i t i s TMR0
retfie ; ??? no , r e t u r n from i n t e r r u p t

TMR0_interrupt ; --- TMR0 interrupt service routine
    bcf INTCON, RBIF
    toto
    btfsc PORTB RB4
    goto toto
	    
    incf PORTD
retfie ; return from interrupt	



	; REGARDER RBIE : NOM DU REGISTRE  : INTCON 
prog_init  ; i n i t i a l i z e your code
    clrf TRISD ; PORTD is an output
    ;clrf TRISB ; PORTD is an output
    
    bsf INTCON , GIE ; a c t i v a t e i n t e r r u p t s
    bsf INTCON , RBIE ; a c t i v a t e TMR0 i n t e r r u p t
    ;bsf INTCON , GIEL ; a c t i v a t e TMR0 i n t e r r u p t
    ;clrf RB0 ; c l e a r the tim e r
    ;clrf RBIF ; c l e a r the tim e r

goto MAIN_LOOP


MAIN_LOOP
    ; --- wait for an interrupt
goto MAIN_LOOP

end
