#include "projet.h"
#define NAME "/aaa"
#define SEMA "/sync2"

int main(){
	int ret;
	pthread_t consumer;
	int fd =shm_open(NAME,O_CREAT|O_RDWR,0644);
	if(ftruncate(fd, 100) == -1){
		printf("erreur ftruncate");
		shm_unlink(NAME);
		return 0;
	}
	sem_t *sem = sem_open(SEMA, O_CREAT, 0644,0);
	ret=pthread_create(&consumer, NULL, receiveMesssage, (void*)&fd);
	if(ret!=0){
		printf("Erreur lors de la creation de consumer\n");
		shm_unlink(NAME);
		return 0;
	}
	sendMessage(fd);
	pthread_join(consumer, NULL);
	ret = sem_close(sem);
	if(ret!=0)
		printf("Erreur lors de la fermeture de la semaphore");
	shm_unlink(NAME);
	return 0;
}

////////////
// wrapper pour faire des test : pour eviter les redondances dans le ss prog send message
////////////
int attente(sem_t *sem, void*ret, char*message){
	strcpy(ret, message);
	sleep(1);
	int test = sem_post(sem);
	return test;
}

void sendMessage(int fd){
	void* ret;
	sem_t *sem=sem_open(SEMA, 0, 0644,0);
	sem_init(sem,0,0);
	ret = mmap(NULL,100,PROT_WRITE,MAP_SHARED,fd,0);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans sendMessage");
		shm_unlink(NAME);
		return;
	}
	
	if(attente(sem, ret, "bonjour")) return;
	if(attente(sem, ret, "salut")) return;
	if(attente(sem, ret, "quit")) return;
}

void *receiveMesssage(void *par){
	int* fd = (int*) par;
	sem_t *sem=sem_open(SEMA, 0, 0644,0);
	char message[100], verif[100] = "quit" ;
	void *ret;
	int test;
	ret = mmap(NULL,100,PROT_READ,MAP_SHARED,*fd,0);

	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans receiveMessage");
		shm_unlink(NAME);
		return NULL;
	}
	while(strcmp(message,verif)){
		printf("La semaphore est liberee : ");
		strcpy(message, (char*)ret);
		printf("message : %s\n", message);
		test = sem_wait(sem);
		if(test == -1)
			return NULL;
		
	}

}