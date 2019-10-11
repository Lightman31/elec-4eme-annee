; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR
#include <p18f4550.inc>
    CONFIG WDT = OFF
    CONFIG MCLRE = ON
    CONFIG DEBUG = ON
    CONFIG LVP = OFF
    CONFIG FOSC = HS
    CONFIG PBADEN = OFF
    
    
    
RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    INIT                   ; go to beginning of program

; TODO ADD INTERRUPTS HERE IF USED

MAIN_PROG CODE                      ; let linker place main program

INIT 
    clrf TRISB
    clrf PORTB
    goto MAIN
 
MAIN
    incf PORTB
    GOTO MAIN                          ; loop forever

    END