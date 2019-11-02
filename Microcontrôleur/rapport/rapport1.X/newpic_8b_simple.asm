#include<p18F4550.inc>

RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    INIT                   ; go to beginning of program

; TODO ADD INTERRUPTS HERE IF USED

MAIN_PROG CODE                      ; let linker place main program

INIT

    GOTO MAIN_LOOP                          
    
MAIN_LOOP
    bsf PORTC , RC0 ; Se t to 1 b i t RC0 o f PORTC (LED ON)
    bcf PORTC , RC0 ; Cl ea r the RC0 b i t o f PORTC (LED OFF)
    GOTO MAIN_LOOP ; loo p back
    END