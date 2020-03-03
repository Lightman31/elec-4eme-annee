#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void sendMessage();
void* receiveMesssage();
int attente(sem_t *sem, void*ret, char*message);