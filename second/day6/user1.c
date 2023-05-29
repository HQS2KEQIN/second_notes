#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
sem_t *sem1;
sem_t *sem2;
void *func(void *asg)
{
	int smp_id = *(int *)asg;
	key_t key = ftok(".",10);
	int share_id = shmget(key,1024,IPC_CREAT|0666);
	char *share_m = (char *)shmat(share_id,NULL,0);
	while(1)
	{
		sem_wait(sem1);
		if(!strcmp(share_m,"quit"))
			break;
		printf("我收到了:%s\n",share_m);

	}
	pthread_exit(NULL);
	
}

int main()
{
	key_t key = ftok(".",10);
	
	int share_id = shmget(key,1024,IPC_CREAT|0666);

	char *share_m = (char *)shmat(share_id,NULL,0);
	int smp_id = semget(key,2,IPC_CREAT|0666);
	sem1 = sem_open("/hqs",O_CREAT,0777,0);
	sem2 = sem_open("/hzm",O_CREAT,0777,0);
	
	pthread_t tid;
	pthread_create(&tid,NULL,func,&smp_id);
 	while(1)
	{		
		scanf("%s",share_m);
		sem_post(sem2);
		if(!strcmp(share_m,"quit"))
			break;		
	}
	pthread_join(tid,NULL);
	shmdt(share_m);
	shmctl(share_id,IPC_RMID,NULL);
	return 0;
	
}