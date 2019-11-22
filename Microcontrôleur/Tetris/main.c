#include "formes.h"

void display(int forme[4][2]);

int main(){
	int forme[4][2]={0};
	int position = 0;
	int x = 0, y = 0;
	for(int i = 0; i<7; i++){
		makeForme(forme, i);
		transformForm(forme, x, y, position);
		display(forme);
	}
	return 0;
}

void display(int forme[4][2]){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++)
			printf("%d", forme[i][j]);
		printf("\n");
	}
	printf("\n\n");
}
