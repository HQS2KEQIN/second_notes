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
	printf("我是信号%d\n",sig);
	exit(0);
}

int main(void)
{
	int x = fork();
	if(x > 0)
	{
		
		signal(SIGRTMAX-8,func);
		printf("parent: PID=%d\n",getpid());
		while(1);
	}
	if(x == 0)
	{
		kill(getppid(),SIGRTMAX-8);//给父进程发送一个信号
		printf("child: kill %d\n",getppid());
	}

	return 0;
}




