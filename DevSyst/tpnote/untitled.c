
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	char stp[100] = "coucou";
	char*test = "ici";

	printf("%s\n", stp);
	printf("%s\n", test);

	printf("%s\n", strcpy(stp,test));

}