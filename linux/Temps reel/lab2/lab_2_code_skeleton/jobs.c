#include <time.h>
#include <stdio.h>


struct timespec diff(struct timespec start, struct timespec end);

void job(long fet) // fet in nanoseconds
{
  struct timespec start, end;
  int exit=0;

  // Statements to create a job whose fixed execution time (CPU time) is equal to fet ...
  clock_gettime(CLOCK_REALIME, &start);
  clock_gettime(CLOCK_REALIME, &end);
  while (!exit){
  	clock_gettime(CLOCK_REALIME, &end);
  	if(fet >= diff(start,end).tv_nsec)
  		exit = 1;
  }

  print("durée du job (en ns) : %ld|prévu : %ld", diff(start,end).tv_nsec, fet);

  // Option: print the time (in ns) elapsed between start and end using the function diff below.
  // This printing option is to be avoided during tests since it penalizes deadlines respectfulness ...  
}

struct timespec diff(struct timespec start, struct timespec end)
{
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}
