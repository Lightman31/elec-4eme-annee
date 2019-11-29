/* 
 * File:   newmain.c
 * Author: Adrian Chazottes
 *
 * Created on 18 novembre 2016, 10:00
 */

#include "main.h"

#pragma config FOSC = HS 		//oscillator HS
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = ON		//Debug ON


void main (void)
{
    // call the function that will init the PIC
    initMyPIC18F();
    glcd_Init(GLCD_ON);
    //glcd_PlotPixel( 2, 2, 0xFF);
    
    int i = 0;
                
    int x,y;
    unsigned char ecran[10][22] = {0};
    unsigned char forme[4][2] = {0};
    unsigned char previous_forme[4][2] = {0};
    
    ecran[0][21] = 1;
    ecran[9][21] = 1;
    ecran[1][21] = 1;
    ecran[0][0] = 1;
    
    forme[0][0] = 1;
    forme[1][0] = 1;
    forme[2][0] = 1;
    forme[3][0] = 1;
    forme[3][1] = 1;
    
    
    
    ecran[5][10] = 1;
    ecran[5][11] = 1;
    ecran[5][12] = 1;
    ecran[6][12] = 1;
    
    // Swith the screen ON

    // Set the cursor and write a string
    glcd_SetCursor(1, 0);

//    glcd_PlotPixel(10,0,1);
//    glcd_PlotPixel(40,0,1);
//    glcd_PlotPixel(10,60,1);
//    glcd_PlotPixel(40,60,1);
    glcd_Rect(1,21,90,62,1);
    glcd_print_tab(ecran);
    
    while(1)
    {
        glcd_draw_shape(previous_forme,0);
            i++;
        glcd_draw_shape(forme,1);
              
  


    for(x=0;x<=1;x++)
      {
         for(y=0;y<=3;y++)
           {
               previous_forme[y][x] =  forme[y][x];
           }
      }
        
        
        forme[i][0] = 1;
        forme[i+1][0] = 1;
        forme[i+2][0] = 1;
        forme[i+3][0] = 1;
        forme[i+3][1] = 1;
        
        if (i == 21) i = 0;
        __delay_us(1000000);
    }

}// end of the main function

// make sure to have an empty LAST line in any *.c file (just hit an Enter)!



