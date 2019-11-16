#include <p18F4550.inc>
CONFIG WDT=OFF ; disable watchdog timer
CONFIG MCLRE = ON ; MCLEAR Pin on
CONFIG DEBUG = OFF ; Disable Debug Mode
CONFIG FOSC = HS ; oscillator mode
org 0x0000 ; reset vector
goto prog_init
org 0x0008 ; interrupt vector
goto irq_handle
; --- IRQ routine
irq_handle
btfsc PIR1, ADIF ; is it AD?
goto AD_interrupt ; yes
retfie ; no, return f.i.
AD_interrupt
bcf PIR1, ADIF ; clear the flag
; A/D result goes into PORTC
movff ADRESH, PORTC
retfie
    ; --- initilaization
prog_init
; PORTA is DDDDDDDA
; ?> only RA0 is analog
; left-justified result
movlw B'00001110'
movwf ADCON1
; select channel 0 -> AN0
movlw B'00000000'
movwf ADCON0
; power up the A/D module
bsf ADCON0, ADON
; initialize PORTC
clrf TRISC ; PORTC is an output
clrf PORTC ; clear PORTC
; configure interrupts
bsf INTCON, GIE ; interrupts
bsf PIE1, ADIE ; AD interrupt
bsf INTCON, PEIE ; periph. Int.
    ; --- Main loop
start_AD
; start the A/D conversion
bsf ADCON0, GO_DONE
goto start_AD
end 