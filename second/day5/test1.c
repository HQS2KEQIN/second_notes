#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	key_t key = ftok(".",10);
	
	int share_id = shmget(key,1024,IPC_CREAT|0666);

	char *share_m = (char *)shmat(share_id,NULL,0);
	int smp_id = semget(key,2,IPC_CREAT|0666);
	semctl(smp_id,0,SETVAL,0);
	semctl(smp_id,1,SETVAL,1);
	int x = fork();
	
	if(x>0)
	{
		struct sembuf buf1 = {0,1,0};
		struct sembuf buf2 = {1,-1,0};
		while(1)
		{
			semop(smp_id,&buf2,1);
			scanf("%s",share_m);
			semop(smp_id,&buf1,1);
			if(!strcmp(share_m,"quit"))
				break;
			
		}
		wait(NULL);
		shmdt(share_m);
		shmctl(share_id,IPC_RMID,NULL);
		semctl(smp_id,0,IPC_RMID);
		semctl(smp_id,1,IPC_RMID);
	}
	if(x==0)
	{
		struct sembuf buf1 = {0,-1,0};
		struct sembuf buf2 = {1,1,0};
		while(1)
		{
			semop(smp_id,&buf1,1);
			printf("我收到了:%s\n",share_m);
			semop(smp_id,&buf2,1);
			if(!strcmp(share_m,"quit"))
				break;
		}
		exit(0);
	}

	return 0;
	
}