#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	
	int file = open("1.txt",O_RDWR);
	char str[12] ={0};
	if(file == -1)
	{
		perror("fail\n");
		return -1;
	}
	pid_t pid = fork();
	if(pid > 0)
	{
		sleep(3);
		read(file,str,12);
		printf("我是父进程，strf = %s\n",str);
		wait(NULL);
	}
	if(pid == 0)
	{
		
		printf("我是子进程,我要把文件关了\n");
		close(file);
		exit(0);
	}
	return 0;
}