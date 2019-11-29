#include "formes.h"

void makeForme(unsigned char forme[4][2], unsigned short i){
	for(unsigned short i = 0; i < 4; i++){
		for(unsigned short j = 0; j < 2; j++)
			forme[i][j] = CHARFALSE;
	}
	switch(i){
		case 0:
			for(unsigned short i = 0; i < 4; i++)
				forme[i][0] = CHARTRUE;
			break;

		case 1:
			for(unsigned short i = 0; i < 2; i++){
				for(unsigned short j = 0; j < 2; j++)
					forme[i][j] = CHARTRUE;
			}
			break;

		case 2:
			for(unsigned short i = 0; i < 3; i++){
					for(unsigned short j = 0; j < 2; j++){
						if(!((i == 0 && j == 1) || (i == 2 && j == 1)))
							forme[i][j] = CHARTRUE;
					}
				}
			break;

		case 3:
			for(unsigned short i = 0; i < 3; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(!((i == 1 && j == 1) || (i == 2 && j == 1)))
						forme[i][j] = CHARTRUE;
				}
			}
			break;

		case 4:
			for(unsigned short i = 0; i < 3; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(!((i == 1 && j == 0) || (i == 2 && j == 0)))
						forme[i][j] = CHARTRUE;
				}
			}
			break;

		case 5:
			for(unsigned short i = 0; i < 3; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(!((i == 0 && j == 1) || (i == 2 && j == 0)))
						forme[i][j] = CHARTRUE;
				}
			}
			break;

		case 6:
			for(unsigned short i = 0; i < 3; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(!((i == 0 && j == 0) || (i == 2 && j == 1)))
						forme[i][j] = CHARTRUE;
				}
			}
			break;
		default:
				for(unsigned short i = 0; i < 4; i++)
					forme[i][0] = CHARTRUE;
			break;
	}
}

void transformForm(unsigned char forme[4][2], unsigned short x, unsigned short y, unsigned short position){
	unsigned short newForme[4][2] = {0};
	unsigned short a = 0;
	switch(position){
		case 0:
			for(unsigned short i = 0; i < 4; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(forme[i][j] == CHARTRUE){
						newForme[a][0] = i+x;
						newForme[a][1] = j+y;
						a++;
					}
				}
			}
			break;
		case 1:
			for(unsigned short i = 0; i < 4; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(forme[i][j] == CHARTRUE){
						newForme[a][0] = 1-j+x;
						newForme[a][1] = i+y;
						a++;
					}
				}
			}
			break;
		case 2:
			for(unsigned short i = 0; i < 4; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(forme[i][j] == CHARTRUE){
						newForme[a][0] = 3 - i+x;
						newForme[a][1] = 1 - j+y;
						a++;
					}
				}
			}
			break;
		case 3:
			for(unsigned short i = 0; i < 4; i++){
				for(unsigned short j = 0; j < 2; j++){
					if(forme[i][j] == CHARTRUE){
						newForme[a][0] = j+x;
						newForme[a][1] = 3-i+y;
						a++;
					}
				}
			}
			break;
	}
	for(unsigned short i = 0; i < 4; i++)
		for(unsigned short j = 0; j < 2; j++)
			forme[i][j] = newForme[i][j];
}

void changePos(unsigned short *position){
	*position = (((*position)+1) % 4);
}
