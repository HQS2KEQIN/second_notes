#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#define FIFO "/home/gec/FIFO"
int fd = -1;

int open_fifo(char *fifopath)
{
	if(access(fifopath,F_OK))
	{
		int ret = mkfifo(fifopath,0777);
		if(ret == -1)
		{
			perror("make fifo error\n");
			return -1;
		}
	}
	
	int fd = open(fifopath,O_RDWR);
	if(fd == -1)
	{
		perror("open fifo error\n");
		return -2;
	}

	return fd;
}

void read_pip(int sig)
{
	char buf[40] = {0};
	read(fd,buf,sizeof(buf));
	printf("我是父进程,我收到了%s\n",buf);
}


int main()
{
	fd = open_fifo(FIFO);
	int x = fork();
	char str[50] = {0};
	if(x > 0 )
	{
		signal(SIGRTMIN,read_pip);
		pause();
	}
		
	if(x == 0)
	{
		bzero(str,sizeof(str));
		printf("我是子进程%d,我要发送",getpid())
		scanf("%s",str);
		write(fd,str,strlen(str));
		kill(getppid(),SIGRTMIN);
	}
	
	
	close(fd);
	
	return 0;
}