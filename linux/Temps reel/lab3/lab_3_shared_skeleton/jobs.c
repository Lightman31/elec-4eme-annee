#include <time.h>
#include <stdio.h>


struct timespec diff(struct timespec start, struct timespec end);

void job(long fet) //in ns
{
  struct timespec start, end;
  int exit=0;

  //Statements to create a job whose fixed execution time (CPU time) is equal to fet ...
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
  while (!exit){
  	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
  	if(fet <= diff(start,end).tv_nsec)
  		exit = 1;
  }
}

long job_with_cpu_time_returned(long fet) //in ns
{
  struct timespec start, end;
  int exit=0;
  
  //Statements to create a job whose fixed execution time (CPU time) is equal to fet ...
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
  while (!exit){
  	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
  	if(fet <= diff(start,end).tv_nsec)
  		exit = 1;
  }
  // Return the measured CPU time ...
  printf("durée du job (en ns) : %ld|prévu : %ld\n", diff(start,end).tv_nsec, fet);
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
