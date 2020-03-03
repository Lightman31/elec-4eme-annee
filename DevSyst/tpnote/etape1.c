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
	ret=pthread_create(&consumer, NULL, receiveMesssage, (void*)&fd);
	if(ret!=0){
		printf("Erreur lors de la creation de consumer\n");
		shm_unlink(NAME);
		return 0;
	}
	sendMessage(fd);
	pthread_join(consumer, NULL);
	shm_unlink(NAME);
	return 0;
}

void sendMessage(int fd){
	char* message = "bonjour";
	void* ret;
	ret = mmap(NULL,100,PROT_WRITE,MAP_SHARED,fd,0);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans sendMessage");
		shm_unlink(NAME);
		return;
	}
	strcpy(ret, message);
	sleep(1);
	message = "salut";
	strcpy(ret, message);
	sleep(1);
	message = "quit";
	strcpy(ret, message);
}

void *receiveMesssage(void *par){
	int* fd = (int*) par;
	char message[100], prevMessage[100], verif[100] = "quit" ;
	void *ret;
	ret = mmap(NULL,100,PROT_READ,MAP_SHARED,*fd,0);

	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans receiveMessage");
		shm_unlink(NAME);
		return NULL;
	}
	while(strcmp(message,verif)){
		strcpy(message, (char*)ret);
		if(strcmp(message,prevMessage))
			printf("message :%s\n", message);
		strcpy(prevMessage, message);
	}

}