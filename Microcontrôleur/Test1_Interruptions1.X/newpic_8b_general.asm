#include <p18F4550.inc>
ORG 0x0000  ;  processor  r e s e t  vector
GOTO prog_init  ;  go  to  beginning  of  program
ORG 0x0008
GOTO irq_handle

MAIN_PROG CODE ;  l e t  l i n k e r  place  main program

irq_handle  ; ??? i n t e r r u p t r o u ti n e
    btfsc INTCON , RBIF
    goto RB_interrupt ; ye s , i t i s PORTB
    
    ; ??? f l a g t e s t ?> i s i t TMR0?
    btfsc INTCON , TMR0IF
    goto TMR0_interrupt ; ye s , i t i s TMR0
    
retfie ; ??? no , r e t u r n from i n t e r r u p t

RB_interrupt ; --- interrupt service routine
    bcf INTCON, RBIF
    
    toto
btfsc PORTB, RB4
    goto toto
btfsc PORTB, RB5
    goto toto
btfsc PORTB, RB6
    goto toto
btfsc PORTB, RB7
    goto toto
	    
    incf PORTD
retfie ; return from interrupt	

TMR0_interrupt
     ; ??? c l e a r the TMR0 i n t e r r u p t f l a g
     bcf INTCON , TMR0IF
     incf PORTC; ??? inc remen t PORTC
retfie

prog_init  ; i n i t i a l i z e your code
    clrf TRISC ; PORTC i s an output

    clrf TRISD ; PORTD is an output
    
    bsf INTCON , GIE ; a c t i v a t e i n t e r r u p t s
    bsf INTCON , RBIE ; a c t i v a t e RB i n t e r r u p t
    
    bsf T0CON , TMR0ON ; TIMER 0 ON
    bsf T0CON , T08BIT ; TIMER 0 on 8 b i t s
    bcf T0CON , T0CS ; i n t e r n a l cl o c k so u r c e
    bcf T0CON , PSA ; gi v e the p r e s c a l e r to TMR0

    bsf INTCON , GIE ; a c t i v a t e i n t e r r u p t s
    bsf INTCON , TMR0IE ; a c t i v a t e TMR0 i n t e r r u p t
    clrf TMR0 ; c l e a r the tim e r

goto MAIN_LOOP


MAIN_LOOP
    ; --- wait for an interrupt
goto MAIN_LOOP

end
