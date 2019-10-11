#include <p18F4550.inc>
    RES_VECT  CODE 0x0000  ;  processor  r e s e t  vector
    GOTO INIT  ;  go  to  beginning  of  program
    
    MAIN_PROG CODE ;  l e t  l i n k e r  place  main program
 
 INIT
 GOTO MAIN_LOOP
 
 MAIN_LOOP
 bsf PORTC , RC0 ;  Set  tobit RC0 of PORTC (LED ON)
 bcf PORTC , RC0 ;  Clear  the RC0 bit  of PORTC (LED OFF)
 GOTO MAIN_LOOP ;  loop  back
 END