/* 
 * File:   newmain.c
 * Author: Adrian Chazottes
 *
 * Created on 18 novembre 2016, 10:00
 */

#include "main.h"
#include "collisions.h"
#include "formes.h"
#include <time.h>
#pragma config FOSC = HS 		//oscillaor HS
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = ON		//Debug ON


void main (void)
{
    /// INITIALISATION ET CLEAN DE LA CARTE ET DU GLCD
    initMyPIC18F();
    glcd_Init(GLCD_ON);
    glcd_SetCursor(1, 0);
    
    /// INITILATION DES VARIABLES POUR LE TETRIS
    srand(time(NULL));
	unsigned char forme[4][2] = {FALSE};
	unsigned char prevForme[4][2] = {FALSE};
	unsigned char tab[HEIGHT_TAB][WIDTH_TAB] = {FALSE};
	unsigned short position = 0;
	unsigned short x = 0, y = 0;
	unsigned short verif = FALSE;
	unsigned short formeEnCours = FALSE;
	unsigned short typeForme = 0;
    // call the function that will init the PIC

    glcd_print_tab(tab);
    
    
    
    while(!verif){
         __delay_us(100000);
		if(!formeEnCours){
			x = 0, y = 4;
			typeForme = rand() % 7;
			position = 0;
			formeEnCours = TRUE;
		}else{
            for(unsigned short i = 0; i < 4; i++){
                for(unsigned short j = 0; j < 2; j++){
                    prevForme[i][j] = forme[i][j];
                }
            }
        }
            if (PORTE == 0x01 && y > 0) y--;
            if (PORTE == 0x02 && ((y < 8 && position % 2) || y < 6)) y++;
            if (PORTE == 0x04) changePos(&position);
			makeForme(forme, typeForme);
			transformForm(forme, x, y, position);
			//Check s'il faut fixer la piece
			if(checkCollision(tab, forme)){
				putPiece(tab, forme);
                formeEnCours = FALSE;
                glcd_draw_shape(prevForme,0);
                glcd_draw_shape(forme,1);
                glcd_print_tab(tab);
                for(unsigned short i = 0; i < 4; i++){
                for(unsigned short j = 0; j < 2; j++){
                    prevForme[i][j] = FALSE;
                }
            }
            }else{
                glcd_draw_shape(prevForme, 0);
                glcd_draw_shape(forme,1);
            }
			//Check s'il faut supprimer la ligne
			for(unsigned short line = 0; line < HEIGHT_TAB; line++)
				if(checkLine(tab, line)){
					eraseLine(tab, line);
                    glcd_print_tab(tab);
                }
            
			x++;
		for(unsigned short i = 0; i < WIDTH_TAB; i++)
				if(tab[0][i] ==  1)
					verif = TRUE;
	}

    
   
    
}// end of the main function

// make sure to have an empty LAST line in any *.c file (just hit an Enter)!



