#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
int i = 0;

void func(int sig)
{
	if(sig==10)
		i+=1;
}

int main()
{
	printf("我是父进程%d\n",getpid());
	sigset_t set;
	signal(SIGUSR1,func);
	signal(SIGUSR2,SIG_IGN);
	for(int i = 0;i<5;i++)
	{
		sleep(1);
		int x = fork();
		
		if(x==0)
		{
			sleep(3);
			printf("我是子进程%d ",getpid());
			if(getpid() == getppid()+1)
			{
				printf("我吃饭\n");
				kill(getppid(),SIGUSR1);
				
			}
			if(getpid() == getppid()+2)
			{
				printf("我睡觉\n");
				kill(getppid(),SIGUSR1);
				
			}
			if(getpid() == getppid()+3)
			{
				printf("我打游戏\n");
				kill(getppid(),SIGUSR1);
				
			}
			if(getpid() == getppid()+4)
			{
				printf("我原\n");
				kill(getppid(),SIGUSR1);
				
			}
			if(getpid() == getppid()+5)
			{
				printf("我崩\n");
				kill(getppid(),SIGUSR2);
				
			}
			
			exit(0);
		}	
	}
	
	while(i<5);
	printf("子进程都发送的一致，准许退出\n");
	return 0;
}