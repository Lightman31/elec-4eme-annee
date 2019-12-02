#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned short formes[4][2] = {0};
	for(unsigned short i = 0; i < 3; i++){
		for(unsigned short j = 0; j < 2; j++){
			if(!((i == 0 && j == 1) || (i == 2 && j == 1)))
				formes[i][j] = 1;
		}
	}
	for(int i = 0; i < 4; i++){
		for(int j =0; j < 2; j++){
			if(formes[i][j])
				printf("‡");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i = 0; i < 2; i++){
		for(int j =0; j < 4; j++){
			if(formes[j][i])
				printf("‡");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i = 3; i >= 0; i--){
		for(int j = 1; j >= 0; j--){
			if(formes[i][j])
				printf("‡");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i = 1; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
			if(formes[j][i])
				printf("‡");
			else
				printf(" ");
		}
		printf("\n");
	}
}




