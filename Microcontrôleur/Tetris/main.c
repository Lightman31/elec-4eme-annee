#include "collisions.h"
#include "formes.h"

void display(unsigned short tabAffichage[HEIGHT_TAB][WIDTH_TAB]);

int main(){
	srand(time(NULL));
	unsigned short forme[4][2] = {FALSE};
	unsigned short tab[HEIGHT_TAB][WIDTH_TAB] = {FALSE};
	unsigned short tabAffichage[HEIGHT_TAB][WIDTH_TAB] = {FALSE};
	unsigned short position = 0;
	unsigned short x = 0, y = 0;
	unsigned short verif = FALSE;
	unsigned short formeEnCours = FALSE;
	unsigned short typeForme = 0;
	unsigned short choix = 0;
	while(!verif){
		if(!formeEnCours){
			x = 0, y = 4;
			typeForme = rand() % 7;
			position = 0;
			formeEnCours = TRUE;
		}else{
			printf("1. Gauche\n2. Droite\n3. Rotate\n4.Nothing");
			scanf("%hu", &choix);
			if(choix == 1)
				y--;
			else if(choix == 2)
				y++;
			else if(choix == 3)
				changePos(&position);

			makeForme(forme, typeForme);
			transformForm(forme, x, y, position);
			//Charger l'affichage du tableau
			for(unsigned short i = 0; i < HEIGHT_TAB; i++)
				for(unsigned short j = 0; j < WIDTH_TAB; j++)
					tabAffichage[i][j] = tab[i][j];
			//Charger l'affichage de la piece
			for(unsigned short i = 0; i < 4; i++)
				tabAffichage[forme[i][0]][forme[i][1]] = TRUE;
			//Check s'il faut fixer la piece
			if(checkCollision(tab, forme))
				putPiece(tab, forme), formeEnCours = FALSE;
			//Check s'il faut supprimer la ligne
			for(unsigned short line = 0; line < HEIGHT_TAB; line++)
				if(checkLine(tab, line))
					eraseLine(tab, line);
			
			x++;
		}
		display(tabAffichage);
		for(unsigned short i = 0; i < WIDTH_TAB; i++)
				if(tab[0][i] ==  1)
					verif = TRUE;
	}
	return 0;
}

void display(unsigned short tabAffichage[HEIGHT_TAB][WIDTH_TAB]){
	for(unsigned short i = 0; i < HEIGHT_TAB; i++){
		for(unsigned short j = 0; j < WIDTH_TAB; j++){
			if(tabAffichage[i][j])
				printf("‡");
			else
				printf(" ");
		}
		printf("\n");
	}
}
