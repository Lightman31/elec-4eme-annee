#include "formes.h"

void makeForme(int forme[4][2], int i){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++)
			forme[i][j] = 0;
	}
	switch(i){
		case 0:
			for(int i = 0; i < 4; i++)
				forme[i][0] = 1;
			break;

		case 1:
			for(int i = 0; i < 2; i++){
				for(int j = 0; j < 2; j++)
					forme[i][j] = 1;
			}
			break;

		case 2:
			for(int i = 0; i < 3; i++){
					for(int j = 0; j < 2; j++){
						if(!((i == 0 && j == 1) || (i == 2 && j == 1)))
							forme[i][j] = 1;
					}
				}
			break;

		case 3:
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 2; j++){
					if(!((i == 1 && j == 1) || (i == 2 && j == 1)))
						forme[i][j] = 1;
				}
			}
			break;

		case 4:
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 2; j++){
					if(!((i == 1 && j == 0) || (i == 2 && j == 0)))
						forme[i][j] = 1;
				}
			}
			break;

		case 5:
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 2; j++){
					if(!((i == 0 && j == 1) || (i == 2 && j == 0)))
						forme[i][j] = 1;
				}
			}
			break;

		case 6:
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 2; j++){
					if(!((i == 0 && j == 0) || (i == 2 && j == 1)))
						forme[i][j] = 1;
				}
			}
			break;
		default:
				for(int i = 0; i < 4; i++)
					forme[i][0] = 1;
			break;
	}
}

void transformForm(int forme[4][2], int x, int y, int position){
	int newForme[4][2] = {0};
	int a = 0;
	switch(position){
		case 0:
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 2; j++){
					if(forme[i][j]){
						newForme[a][0] = i+x;
						newForme[a][1] = j+y;
						a++;
					}
				}
			}
			break;
		case 1:
			for(int i = 0; i < 2; i++){
				for(int j = 0; j < 4; j++){
					if(forme[i][j]){
						newForme[a][0] = i+x;
						newForme[a][1] = j+y;
						a++;
					}
				}
			}
			break;
		case 2:
			for(int i = 3; i >= 0; i--){
				for(int j = 1; j >= 0; j--){
					if(forme[i][j]){
						newForme[a][0] = i+x;
						newForme[a][1] = j+y;
						a++;
					}
				}
			}
			break;
		case 3:
			for(int i= 1; i >= 0; i--){
				for(int j = 3; j >= 0; j--){
					if(forme[i][j]){
						newForme[a][0] = i+x;
						newForme[a][1] = j+y;
						a++;
					}
				}
			}
			break;
	}
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 2; j++)
			forme[i][j] = newForme[i][j];
}

void changePos(int *position){
	*position = ++(*position) % 4;
}
