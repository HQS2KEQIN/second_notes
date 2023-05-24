#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main()
{
	pid_t pid;
	int i;
	for(i=1;i<=5;i++)
	{
		sleep(1);
		pid = fork();
		if(pid==0)
		{
			break;		
		}
	}
	if(pid>0)
	{
		printf("我是父进程，我有五个儿子\n");
	}
	if(pid==0) 
	{
		sleep(5);
		printf("我是子进程%d 我的ID是:%d pid是%d\n",i,getpid(),getppid());
		
	}
	while(1);
	return 0;
	
}
