#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <signal.h>

void printMessage(int sig);

int main(){
	int stat; 
    pid_t pid; 
    if(fork() == 0){
      printf("Hello\n");
      while(1);
    }
    else
    { 
      printf("NSM");
    	signal(SIGUSR1, printMessage);
    //     kill(pid, SIGINT); 
    //     wait(&stat); 
    //    if (WIFSIGNALED(stat)) 
    //         psignal(WTERMSIG(stat), "Child term due to"); 
    }  
}

void printMessage(int sig){
	printf("Signal reçu %d", sig);
}