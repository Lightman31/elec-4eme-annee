# 1 "init.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "init.c" 2
# 1 "./init.h" 1
# 16 "./init.h"
void initMyPIC18F(void);
# 1 "init.c" 2



void initMyPIC18F(void)
{

 ADCON1 = 0x0F ;
 ADCON0 = 0;


 TRISA = 0x00;
 TRISB = 0x00;
 TRISC = 0x00;
 TRISD = 0x00;
 TRISE = 0x00;


 PORTA = 0x00;
 PORTB = 0x00;
 PORTC = 0x00;
 PORTD = 0x00;


 PORTE = 0x00;

}
