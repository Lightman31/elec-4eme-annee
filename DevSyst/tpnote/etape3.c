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
int attente(sem_t *sem, void*ret, char message[20]){
	t_entry entry;
	entry.free = 0;
	strcpy(entry.msg,message);
	ret += entry;
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
	
	if(attente(sem, ret, "message0")) return;
	if(attente(sem, ret, "message1")) return;
	if(attente(sem, ret, "message2")) return;
	if(attente(sem, ret, "message3")) return;
	if(attente(sem, ret, "message4")) return;
	if(attente(sem, ret, "message5")) return;
	if(attente(sem, ret, "message6")) return;
	if(attente(sem, ret, "message7")) return;
	if(attente(sem, ret, "message8")) return;
	if(attente(sem, ret, "message9")) return;
}

void *receiveMesssage(void *par){
	int* fd = (int*) par;
	sem_t *sem=sem_open(SEMA, 0, 0644,0);
	char message[100], verif[100] = "quit" ;
	void *ret;
	int test;
	t_entry entries[10];
	ret = mmap(NULL,100,PROT_READ,MAP_SHARED,*fd,0);
	sleep(1);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans receiveMessage");
		shm_unlink(NAME);
		return NULL;
	}
	entries = (t_entries) &ret;
	for(int i = 0; i < 10; i++){
		printf("message : %s\n", entries[i].msg);
		test = sem_wait(sem);
		if(test == -1)
			return NULL;
		
	}

}