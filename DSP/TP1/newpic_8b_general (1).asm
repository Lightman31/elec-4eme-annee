#include <p18F4550.inc>
    RES_VECT  CODE 0x0000  ;  processor  r e s e t  vector
    GOTO INIT  ;  go  to  beginning  of  program
    
    MAIN_PROG CODE ;  l e t  l i n k e r  place  main program
 
 INIT
 ;  Declare  v a r i a b l e s  at  2 memory  l o c a t i o n s  on  the DM.
    count1  equ H'00'  ;  count1  address
    count2  equ H'01'  ;  count2  address
    GOTO prog_start
 
prog_start
    clrf  TRISD ;  set PORTC as  output
    clrf PORTD ;  clear PORTC
    clrf  TRISC ;  set PORTC as  output
    clrf PORTC ;  clear PORTC
    GOTO MAIN_LOOP
 
 MAIN_LOOP
    call my_delay ;
    
    bsf PORTC, RC0 ;  Set  tobit RC0 of PORTC (LED ON)
    bcf PORTC, RC1 ;  Set  tobit RC0 of PORTC (LED ON)
    bsf PORTC , RC2 ;  Set  tobit RC0 of PORTC (LED ON)
      PORTD ;  Count port D
    
     call my_delay ;
    bcf PORTC , RC0 ;  Clear  the RC0 bit  of PORTC (LED OFF)
    bsf PORTC, RC1 ;  Clear  the RC0 bit  of PORTC (LED OFF)
    bcf PORTC , RC2 ;  Clear  the RC0 bit  of PORTC (LED OFF)
   SHL  PORTD ;  Count port D
   
    
    GOTO MAIN_LOOP ;  loop  back
    
    my_delay
	decfsz  count2	
	goto my_delay
	decfsz  count1
	goto my_delay
	return

    
    END
 
 
 
 
 
 