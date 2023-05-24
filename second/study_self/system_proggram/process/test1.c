#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	int a = 10;
	sleep(5);
	int pid = fork();
	
	if(pid > 0)
	{
		
		printf("我是父进程,我pid是%d\n",getpid());
		while(1);
	}
	else if(pid == 0)
	{
		printf("我是子进程,我的pid是%d,我的ppid是%d\n",getpid(),getppid());
	}
	return 0;
}