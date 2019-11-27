/*
 * File:   newmain.c
 * Author: Utilisateur
 *
 * Created on 22 novembre 2019, 10:47
 */


#include "main.h"

#pragma config FOSC = HS 		//oscillator HS
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = ON		//Debug ON

void main(void) {
    initMyPIC18F();
    // Swith the screen ON
    glcd_Init(GLCD_ON);
    glcd_Image();   

while (1)
{
    // Clear the screen
    glcd_FillScreen(0);
    // Set the cursor and write a string
    glcd_SetCursor(1, 0);
    glcd_WriteString("HELLO !", f8X8, 1);
    
    while (1){}
}
    return ;
}


