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


void recv_data(int sig)
{
	char buf[50];
	bzero(buf,sizeof(buf));
	read(fd,buf,sizeof(buf));
	printf("接收到 %s\n",buf);
	if(!strncmp(buf,"quit",4))
		exit(0);
}

int get_pid(void)
{
	pid_t pid,mypid;
	//先从管道中获取对方的PID号
	read(fd,&pid,sizeof(pid));
	//再将自己的PID号发送过去
	mypid = getpid();
	write(fd,&mypid,sizeof(mypid));
	kill(pid,SIGUSR2);//发送信号提醒对方接收
	return pid;//将对方的PID号返回
}

int main(void)
{
	//打开管道
	fd = open_fifo(FIFO);
	//获取对方的PID号
	pid_t PID = get_pid();
	printf("mypid=%d,pid=%d\n",getpid(),PID);
	//声明信号处理函数
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




