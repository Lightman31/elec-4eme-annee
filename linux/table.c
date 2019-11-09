#include <stdio.h>
#include <stdlib.h>

int* fill_table(unsigned int);
void print_cell(int*, unsigned int);

int* fill_table(unsigned int size)
{
  int* T;
  int i;
  
  T = (int*)malloc(size * sizeof(int));
  for (i=0; i<size; i++)
    T[i] = i;
  return T;
}

void print_cell(int* T, unsigned int j)
{
  printf("%d\n", T[j]);
}


int main(void)
{ 
  int* T;

  T = fill_table(10);
  print_cell(T,1000);
   
  return 0; 
} 
