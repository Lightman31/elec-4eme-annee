#include "projet.h"
#define NAME "/aaa"
int main(){
	int ret;
	pthread_t producer, consumer;
	int fd =shm_open(NAME,O_CREAT|O_RDWR,0644);
	if(ftruncate(fd, 100) == -1){
		printf("erreur ftruncate");
		shm_unlink(NAME);
		return 0;
	}
	//sem_t *sem = sem_open("./sync1", O_CREAT, 0644,1);
	/*ret=pthread_create(&producer,NULL,sendMessage,(void*) sem);
	if(ret!=0){
		printf("Erreur lors de la creation de producer\n");
		return 0;
	}*/
	ret=pthread_create(&consumer, NULL, receiveMesssage, (void*)&fd);
	if(ret!=0){
		printf("Erreur lors de la creation de consumer\n");
		shm_unlink(NAME);
		return 0;
	}
	sendMessage(fd);
	pthread_join(consumer, NULL);
	/*ret = sem_close(sem);
	if(ret!=0)
		printf("Erreur lors de la fermeture de la semaphore");
	*/
	shm_unlink(NAME);
	return 0;
}

void sendMessage(int fd){
	char* message = "quit";
	void* ret;
	ret = mmap(NULL,100,PROT_WRITE,MAP_SHARED,fd,0);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans sendMessage");
		shm_unlink(NAME);
		return;
	}
	strcpy(ret, message);
}

void *receiveMesssage(void *par){
	int* fd = (int*) par;
	char message[100] = "allo", prevMessage[100] ;
	void *ret;

	while(message !="quit"){
		ret = mmap(NULL,100,PROT_READ,MAP_SHARED,*fd,0);
		if(ret == MAP_FAILED){
			printf("erreur lors de mmap dans receiveMessage");
			shm_unlink(NAME);
			return NULL;
		}
		printf("%s\n",(char*) ret);

		strcpy(message, (char*)ret);
		if(prevMessage != message)
			printf("message :%s", message);
		strcpy(prevMessage, message);
	}

}