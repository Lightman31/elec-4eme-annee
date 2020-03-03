#include "projet.h"
#define NAME "/aaa"
#define SEMA "/sync2"


void attente(t_entry entries[10], int i, sem_t *sem, void*ret, char message[20]);

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
void attente(t_entry entries[10], int i, sem_t *sem, void*ret, char message[20]){
	entries[i].free = 0;
	strcpy(entries[i].msg,message);
}

void sendMessage(int fd){
	void* ret;
	int test;
	sem_t *sem=sem_open(SEMA, 0, 0644,0);
	sem_init(sem,0,0);
	ret = mmap(NULL,100,PROT_WRITE,MAP_SHARED,fd,0);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans sendMessage");
		shm_unlink(NAME);
		return;
	}
	t_entry entries[10];
	attente(entries,0, sem, ret, "message0");
	attente(entries,1, sem, ret, "message1");
	attente(entries,2, sem, ret, "message2");
	attente(entries,3, sem, ret, "message3");
	attente(entries,4, sem, ret, "message4");
	attente(entries,5, sem, ret, "message5");
	attente(entries,6, sem, ret, "message6");
	attente(entries,7, sem, ret, "message7");
	attente(entries,8, sem, ret, "message8");
	attente(entries,9, sem, ret, "message9");
	for(int i = 0; i < 10; i++){
		strcat(ret, (char*)&(entries[i].free));
		strcat(ret, entries[i].msg);
		strcat(ret, "\n");
		test = sem_post(sem);
		if(test == -1)
			return;
	}
}

void *receiveMesssage(void *par){
	int* fd = (int*) par;
	sem_t *sem=sem_open(SEMA, 0, 0644,0);
	void *ret;
	int tailleRet, tailleMsg;
	char ligne [100];
	int test;
	int i,j= 0, cara = 0;
	char chaine[1024];
	t_entry entries[10];
	ret = mmap(NULL,100,PROT_READ,MAP_SHARED,*fd,0);
	sleep(5);
	if(ret == MAP_FAILED){
		printf("erreur lors de mmap dans receiveMessage");
		shm_unlink(NAME);
		return NULL;
	}

	strcpy(chaine,(char*)ret);

	tailleRet = strlen(chaine);
    //printf("\ntaille : %d\n",tailleRet);
	for (i = 0 ; i < tailleRet ; i++)
	{

		if (chaine[i] == '\n')
		{
			entries[j].free = 1;
			j = j+1;
			cara = 0;

		}
		else 
		{
			entries[j].msg[cara] = chaine[i];
			cara = cara + 1;
		}
		//if (j == 10) break;

	}


	for(i = 0; i < 10; i++){

		printf("%d message : %s\n", entries[i].free,entries[i].msg);
		entries[i].free = 1;
		test = sem_wait(sem);
		if(test == -1)
			return NULL;
		
	}
	

}