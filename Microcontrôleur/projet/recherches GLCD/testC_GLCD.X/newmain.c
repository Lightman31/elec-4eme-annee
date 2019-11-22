/*
 * File:   newmain.c
 * Author: Utilisateur
 *
 * Created on 22 novembre 2019, 10:47
 */


#include <xc.h>
#include "glcd.h"

#pragma config FOSC = HS
#pragma config LVP = OFF


void main(void) {
    // Swith the screen ON
glcd_Init(GLCD_ON);
while (1)
{
    // Clear the screen
    glcd_FillScreen(0);
    // Set the cursor and write a string
    glcd_SetCursor(1, 0);
    glcd_WriteString("HELLO !", f8X8, 1);
    
    while (1){}
}
    return;
}

