/* 
 * File:   newmain.c
 * Author: Adrian Chazottes
 *
 * Created on 18 novembre 2016, 10:00
 */

#include "main.h"
#include "collisions.h"
#include "formes.h"
#include "data.h"
#include <time.h>
#pragma config FOSC = HS 		//oscillaor HS
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = ON		//Debug ON

void menu();
void menuTetris();
void affMenu();

void main (void)
{
    /// INITIALISATION ET CLEAN DE LA CARTE ET DU GLCD
    initMyPIC18F();
    glcd_Init(GLCD_ON);
    glcd_SetCursor(1, 0);
    
    //lancement de la musique
    PORTCbits.RC0 = 1;
    menu();
    
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
    unsigned short delay = 0;
    unsigned short points = 0;
    // call the function that will init the PIC

    glcd_print_tab(tab);

    while(!verif){
        if(!(delay % 20) && formeEnCours){
            if (PORTE == 0x01 && y > 0 && !tab[x][y - 1]&& !tab[x+1][y - 1]&& !tab[x+2][y - 1]&& !tab[x+3][y - 1]) y--;
            if (PORTE == 0x02  && !tab[x][y + 1]&& !tab[x+1][y - 1]&& !tab[x+2][y - 1]&& !tab[x+3][y - 1] 
                    && ((y < 8 && !(position % 2)) || (typeForme && y < 7) || (!typeForme && y < 9&& !(position % 2)) || (!typeForme && y < 6))) y++;
            if (PORTE == 0x04 && typeForme != 1) changePos(&position);
            if(PORTE == 0x01 || PORTE == 0x02 || PORTE == 0x04){
                makeForme(forme, typeForme);
                transformForm(forme, x, y, position);
                glcd_draw_shape(prevForme, 0);
                glcd_draw_shape(forme,1);
            }
        }
			//Check s'il faut fixer la piece
        if(!(delay % 50) && formeEnCours){
            makeForme(forme, typeForme);
            transformForm(forme, x, y, position);
            glcd_draw_shape(prevForme, 0);
            glcd_draw_shape(forme,1);
            x++;
        }
        delay++;
        if(!formeEnCours){
			x = 0, y = 4;
			typeForme = rand() % 7;
			position = 0;
			formeEnCours = TRUE;
		}else if(checkCollision(tab, forme)){
            putPiece(tab, forme, points);
            glcd_draw_shape(prevForme,0);
            glcd_draw_shape(forme,1);
            glcd_print_tab(tab);
            for(unsigned short i = 0; i < 4; i++){
                for(unsigned short j = 0; j < 2; j++){
                    prevForme[i][j] = FALSE;
                }
            }
            for(unsigned short i = 0; i < 4; i++){
                for(unsigned short j = 0; j < 2; j++){
                    forme[i][j] = FALSE;
                }
            }
            delay = 0;
            for(unsigned short i = 0; i < WIDTH_TAB; i++)
                    if(tab[0][i] ==  1)
                        verif = TRUE, points = 0;
           formeEnCours = FALSE;
        }else{
            for(unsigned short i = 0; i < 4; i++){
                for(unsigned short j = 0; j < 2; j++){
                    prevForme[i][j] = forme[i][j];
                }
            }
        }
        for(unsigned short line = 0; line < HEIGHT_TAB; line++)
            if(checkLine(tab, line)){
                eraseLine(tab, line, points);
                points++;
                glcd_print_tab(tab);
            }
        
        if(points % 2){
            PORTCbits.RC1 = 1;
        }
        else PORTCbits.RC1 = 0;
        if(points == 2 || points == 6 || points == 7){
            PORTCbits.RC2 = 1;
        }else PORTCbits.RC2 = 0;
        if(points == 6 || points == 7){
            PORTCbits.RC5 = 1;
        }else PORTCbits.RC5 = 0;
	}
    
    
    
    // son de perte
    PORTCbits.RC0 = 0;
    __delay_us(200000);
    PORTCbits.RC0 = 1;
    
}// end of the main function

// make sure to have an empty LAST line in any *.c file (just hit an Enter)!

void menu()
{
    int fin = 0;
    glcd_FillScreen(0);

     affMenu();
     
    while(fin == 0)
    {
        
        if (PORTE == 0x01)
        {
            menuTetris();
            __delay_us(2000000);
            affMenu();
        }
        if (PORTE == 0x02)
        {
            glcd_FillScreen(0);
            fin = 1;
        }
    }
    
}

void affMenu()
{
    glcd_FillScreen(0);
    //M
    glcd_PlotPixel(10,60,1);
    glcd_PlotPixel(11,59,1);
    glcd_PlotPixel(12,58,1);
    glcd_PlotPixel(11,57,1);
    glcd_PlotPixel(10,56,1);
    glcd_PlotPixel(11,56,1);
    glcd_PlotPixel(12,56,1);
    glcd_PlotPixel(13,56,1);
    glcd_PlotPixel(14,56,1);
    glcd_PlotPixel(15,56,1);
    glcd_PlotPixel(16,56,1);
    glcd_PlotPixel(11,60,1);
    glcd_PlotPixel(12,60,1);
    glcd_PlotPixel(13,60,1);
    glcd_PlotPixel(14,60,1);
    glcd_PlotPixel(15,60,1);
    glcd_PlotPixel(16,60,1);
    
    //E
    glcd_PlotPixel(10,53,1);
    glcd_PlotPixel(10,52,1);
    glcd_PlotPixel(10,51,1);
    glcd_PlotPixel(11,53,1);
    glcd_PlotPixel(12,53,1);
    glcd_PlotPixel(13,53,1);
    glcd_PlotPixel(14,53,1);
    glcd_PlotPixel(15,53,1);
    glcd_PlotPixel(16,53,1);
    glcd_PlotPixel(16,52,1);
    glcd_PlotPixel(16,51,1);
    glcd_PlotPixel(13,52,1);
    
    //N
    glcd_PlotPixel(10,47,1);
    glcd_PlotPixel(11,47,1);
    glcd_PlotPixel(11,46,1);
    glcd_PlotPixel(12,45,1);
    glcd_PlotPixel(13,44,1);
    glcd_PlotPixel(14,43,1);
    glcd_PlotPixel(15,42,1);
    glcd_PlotPixel(12,47,1);
    glcd_PlotPixel(13,47,1);
    glcd_PlotPixel(16,47,1);
    glcd_PlotPixel(13,47,1);
    glcd_PlotPixel(14,47,1);
    glcd_PlotPixel(15,47,1);
    glcd_PlotPixel(10,41,1);
    glcd_PlotPixel(11,41,1);
    glcd_PlotPixel(12,41,1);
    glcd_PlotPixel(13,41,1);
    glcd_PlotPixel(14,41,1);
    glcd_PlotPixel(15,41,1);
    glcd_PlotPixel(16,41,1);

    //U
    glcd_PlotPixel(10,38,1);
    glcd_PlotPixel(11,38,1);
    glcd_PlotPixel(12,38,1);
    glcd_PlotPixel(13,38,1);
    glcd_PlotPixel(14,38,1);
    glcd_PlotPixel(15,38,1);
    glcd_PlotPixel(16,38,1);
    glcd_PlotPixel(10,35,1);
    glcd_PlotPixel(11,35,1);
    glcd_PlotPixel(12,35,1);
    glcd_PlotPixel(13,35,1);
    glcd_PlotPixel(14,35,1);
    glcd_PlotPixel(15,35,1);
    glcd_PlotPixel(16,35,1);
    glcd_PlotPixel(16,36,1);
    glcd_PlotPixel(16,37,1);


    //0
    glcd_PlotPixel(30,60,1);
    glcd_PlotPixel(30,59,1);
    glcd_PlotPixel(30,58,1);
    glcd_PlotPixel(31,60,1);
    glcd_PlotPixel(32,60,1);
    glcd_PlotPixel(33,60,1);
    glcd_PlotPixel(34,60,1);
    glcd_PlotPixel(35,60,1);
    glcd_PlotPixel(36,60,1);
    glcd_PlotPixel(30,57,1);
    glcd_PlotPixel(31,57,1);
    glcd_PlotPixel(32,57,1);
    glcd_PlotPixel(33,57,1);
    glcd_PlotPixel(34,57,1);
    glcd_PlotPixel(35,57,1);
    glcd_PlotPixel(36,57,1);
    glcd_PlotPixel(36,58,1);
    glcd_PlotPixel(36,59,1);   

		//R
    glcd_PlotPixel(30,48,1);
    glcd_PlotPixel(30,47,1);
    glcd_PlotPixel(30,46,1);
    glcd_PlotPixel(31,45,1);
    glcd_PlotPixel(32,45,1);
    glcd_PlotPixel(33,45,1);
    glcd_PlotPixel(33,46,1);
    glcd_PlotPixel(33,47,1);
    glcd_PlotPixel(34,47,1);
    glcd_PlotPixel(35,46,1);
    glcd_PlotPixel(36,45,1);
    glcd_PlotPixel(31,48,1);
    glcd_PlotPixel(32,48,1);
    glcd_PlotPixel(33,48,1);
    glcd_PlotPixel(34,48,1);
    glcd_PlotPixel(35,48,1);
    glcd_PlotPixel(36,48,1);

		//E
    glcd_PlotPixel(30,43,1);
    glcd_PlotPixel(30,42,1);
    glcd_PlotPixel(30,41,1);
    glcd_PlotPixel(31,43,1);
    glcd_PlotPixel(32,43,1);
    glcd_PlotPixel(33,43,1);
    glcd_PlotPixel(34,43,1);
    glcd_PlotPixel(35,43,1);
    glcd_PlotPixel(36,43,1);
    glcd_PlotPixel(36,42,1);
    glcd_PlotPixel(36,41,1);
    glcd_PlotPixel(33,42,1);

    //l
    glcd_PlotPixel(30,38,1);
    glcd_PlotPixel(31,38,1);
    glcd_PlotPixel(32,38,1);
    glcd_PlotPixel(33,38,1);
    glcd_PlotPixel(34,38,1);
    glcd_PlotPixel(35,38,1);
    glcd_PlotPixel(36,37,1);


    //1
    glcd_PlotPixel(41,60,1);
    glcd_PlotPixel(40,59,1);
    glcd_PlotPixel(41,59,1);
    glcd_PlotPixel(42,59,1);
    glcd_PlotPixel(43,59,1);
    glcd_PlotPixel(44,59,1);
    glcd_PlotPixel(45,59,1);
    glcd_PlotPixel(46,59,1);

    //J
    glcd_PlotPixel(40,44,1);
    glcd_PlotPixel(40,45,1);
    glcd_PlotPixel(40,46,1);
    glcd_PlotPixel(40,47,1);
    glcd_PlotPixel(40,48,1);
    glcd_PlotPixel(41,45,1);
    glcd_PlotPixel(42,45,1);
    glcd_PlotPixel(43,45,1);
    glcd_PlotPixel(44,45,1);
    glcd_PlotPixel(45,45,1);
    glcd_PlotPixel(46,46,1);
    glcd_PlotPixel(46,47,1);
    glcd_PlotPixel(46,48,1);

		//E
    glcd_PlotPixel(40,43,1);
    glcd_PlotPixel(40,42,1);
    glcd_PlotPixel(40,41,1);
    glcd_PlotPixel(41,43,1);
    glcd_PlotPixel(42,43,1);
    glcd_PlotPixel(43,43,1);
    glcd_PlotPixel(44,43,1);
    glcd_PlotPixel(45,43,1);
    glcd_PlotPixel(46,43,1);
    glcd_PlotPixel(46,42,1);
    glcd_PlotPixel(46,41,1);
    glcd_PlotPixel(43,42,1);

    //U
    glcd_PlotPixel(40,38,1);
    glcd_PlotPixel(41,38,1);
    glcd_PlotPixel(42,38,1);
    glcd_PlotPixel(43,38,1);
    glcd_PlotPixel(44,38,1);
    glcd_PlotPixel(45,38,1);
    glcd_PlotPixel(46,38,1);
    glcd_PlotPixel(40,35,1);
    glcd_PlotPixel(41,35,1);
    glcd_PlotPixel(42,35,1);
    glcd_PlotPixel(43,35,1);
    glcd_PlotPixel(44,35,1);
    glcd_PlotPixel(45,35,1);
    glcd_PlotPixel(46,35,1);
    glcd_PlotPixel(46,36,1);
    glcd_PlotPixel(46,37,1);
}

void menuTetris()
{
     glcd_FillScreen(0);
     
/*
		//R
    glcd_PlotPixel(30,48,1);
    glcd_PlotPixel(30,47,1);
    glcd_PlotPixel(30,46,1);
    glcd_PlotPixel(31,45,1);
    glcd_PlotPixel(32,45,1);
    glcd_PlotPixel(33,45,1);
    glcd_PlotPixel(33,46,1);
    glcd_PlotPixel(33,47,1);
    glcd_PlotPixel(34,47,1);
    glcd_PlotPixel(35,46,1);
    glcd_PlotPixel(36,45,1);
    glcd_PlotPixel(31,48,1);
    glcd_PlotPixel(32,48,1);
    glcd_PlotPixel(33,48,1);
    glcd_PlotPixel(34,48,1);
    glcd_PlotPixel(35,48,1);
    glcd_PlotPixel(36,48,1);

		//E
    glcd_PlotPixel(30,43,1);
    glcd_PlotPixel(30,42,1);
    glcd_PlotPixel(30,41,1);
    glcd_PlotPixel(31,43,1);
    glcd_PlotPixel(32,43,1);
    glcd_PlotPixel(33,43,1);
    glcd_PlotPixel(34,43,1);
    glcd_PlotPixel(35,43,1);
    glcd_PlotPixel(36,43,1);
    glcd_PlotPixel(36,42,1);
    glcd_PlotPixel(36,41,1);
    glcd_PlotPixel(33,42,1);

    //l
    glcd_PlotPixel(30,38,1);
    glcd_PlotPixel(31,38,1);
    glcd_PlotPixel(32,38,1);
    glcd_PlotPixel(33,38,1);
    glcd_PlotPixel(34,38,1);
    glcd_PlotPixel(35,38,1);
    glcd_PlotPixel(36,37,1);
    */
    //T
    glcd_draw_cube(1,5,1);
    glcd_draw_cube(2,5,1);
    glcd_draw_cube(3,5,1);
    glcd_draw_cube(2,6,1);
    glcd_draw_cube(2,7,1);
    glcd_draw_cube(2,8,1);
    glcd_draw_cube(2,9,1);
    
    //E
    glcd_draw_cube(4,5,1);
    glcd_draw_cube(5,5,1);
    glcd_draw_cube(4,6,1);
    glcd_draw_cube(4,7,1);
    glcd_draw_cube(5,7,1);
    glcd_draw_cube(4,8,1);
    glcd_draw_cube(4,9,1);
    glcd_draw_cube(5,9,1);
    
    //T
    glcd_draw_cube(6,5,1);
    glcd_draw_cube(7,5,1);
    glcd_draw_cube(8,5,1);
    glcd_draw_cube(7,6,1);
    glcd_draw_cube(7,7,1);
    glcd_draw_cube(7,8,1);
    glcd_draw_cube(7,9,1);
    //R
    glcd_draw_cube(9,5,1);
    glcd_draw_cube(10,5,1);
    glcd_draw_cube(11,6,1);
    glcd_draw_cube(10,7,1);
    glcd_draw_cube(11,8,1);
    glcd_draw_cube(11,9,1);
    glcd_draw_cube(9,6,1);
    glcd_draw_cube(9,7,1);
    glcd_draw_cube(9,8,1);
    glcd_draw_cube(9,9,1);
    
    //I
    glcd_draw_cube(13,5,1);
    glcd_draw_cube(13,6,1);
    glcd_draw_cube(13,7,1);
    glcd_draw_cube(13,8,1);
    glcd_draw_cube(13,9,1);
    
}

