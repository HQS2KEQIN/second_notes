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
pid_t PID = -1;

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


void recv_data(int sig)
{
	char buf[50];
	bzero(buf,sizeof(buf));
	read(fd,buf,sizeof(buf));
	printf("接收到 %s\n",buf);
	if(!strncmp(buf,"quit",4))
		exit(0);
}

void read_pid(int sig)
{
	int ret = read(fd,&PID,sizeof(PID));
	if(ret <= 0)
	{
		perror("read pid error\n");
		exit(0);
	}
}

int get_pid(void)
{
	pid_t mypid;
	signal(SIGUSR2,read_pid);
	//先将自己的PID号发送过去
	mypid = getpid();
	write(fd,&mypid,sizeof(mypid));
	//等待对方发送PID号过来
	while(PID == -1);//等待接收到对方的PID号以后再退出
}

int main(void)
{
	fd = open_fifo(FIFO);
	
	get_pid();
	printf("mypid=%d,pid=%d\n",getpid(),PID);
	
	signal(SIGUSR1,recv_data);
	char buf[50];
	while(1)
	{
		bzero(buf,sizeof(buf));
		scanf("%s",buf);
		write(fd,buf,strlen(buf));//往管道中写入数据
		kill(PID,SIGUSR1);//发送一个信号去提醒对方接收
		if(!strncmp(buf,"quit",4))
			break;
	}
	
	close(fd);
	return 0;
}




