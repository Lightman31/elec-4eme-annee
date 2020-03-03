#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct Entry{
	int free;
	char msg[20];
}t_entry;

void sendMessage();
void* receiveMesssage();