#include "collisions.h"

unsigned short checkCollision(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned char forme[4][2]){
	unsigned short result = FALSE; 
	for(unsigned short i = 0; i < 4; i++){
		if(tab[forme[i][0] + 1][forme[i][1]] == CHARTRUE || forme[i][0] + 1 == HEIGHT_TAB){
			result = TRUE;
			break;
		}
	}
	return result;
}

void putPiece(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned char forme[4][2]){
	for(unsigned short i = 0; i < 4; i++){
		tab[forme[i][0]][forme[i][1]] = CHARTRUE;
	}
}

unsigned short checkLine(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned short line){
	unsigned short nbTrue = 0;
	for(unsigned short i = 0; i < WIDTH_TAB; i++){
		if(tab[line][i] == CHARTRUE)
			nbTrue++;
	}
	if(nbTrue + 1 == WIDTH_TAB)
		return TRUE;
	else
		return FALSE;
}

void eraseLine(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned short line){
	for(unsigned short i = line; i > 0; i--){
		for(unsigned short j = 0; j < WIDTH_TAB; j++){
			tab[i][j] = tab[i-1][j];
		}
	}
	for(unsigned short j = 0; j < WIDTH_TAB; j++){
			tab[0][j] = CHARFALSE;
		}
}