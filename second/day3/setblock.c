#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>


void func(int sig)
{
	
	printf("收到信号%d\n",sig);
}


int main()
{

	int x = fork();
	if(x > 0)
	{
		signal(SIGRTMIN,func);
		signal(SIGRTMAX,func);
		sigset_t *set =(sigset_t*)malloc(sizeof(sigset_t));
		sigemptyset(set);
		sigaddset(set,SIGRTMIN);
		sigaddset(set,SIGRTMAX);
		sigprocmask(SIG_BLOCK,set,NULL);
		sleep(4);
		sigprocmask(SIG_UNBLOCK,set,NULL);
	}
	
	if (x==0)
	{
		sleep(1);
		for(int i = 0;i<5;i++)
		{
			kill(getppid(),SIGRTMIN);
		}
		for(int i = 0;i<5;i++)
		{
			kill(getppid(),SIGRTMAX);
		}
		printf("发送完毕\n");
		
	}
	return 0;
}