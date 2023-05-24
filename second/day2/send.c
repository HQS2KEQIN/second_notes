#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define	FIFO1	"/home/gec/FIFO1"
#define	FIFO2	"/home/gec/FIFO2"

int open_pipe(char *path)
{
	if(access(path,F_OK))
	{
		int ret = mkfifo(path,0777);
		if(ret == -1)
		{
			perror("create fail\n");
			return -1;
		}
	}
	int fd = open(path,O_RDWR);
	if(fd == -1)
		perror("open fail\n");
	return fd;
}



int main()
{
	int x = fork();
	char str[50] = {0};
	if(x>0)
	{
		
		int fd = open_pipe(FIFO1);
		while(1)
		{
			bzero(str,sizeof(str));
			scanf("%s",str);
			write(fd,str,strlen(str));
			if(!strcmp(str,"quit"))
				break;
		}
		wait(NULL);
	}
	if(x == 0)
	{
		int fd = open_pipe(FIFO2);
		while(1)
		{
			bzero(str,sizeof(str));
			read(fd,str,sizeof(str));
			if(!strcmp(str,"quit"))
				break;
			printf("我收到了:%s\n",str);
		}
		exit(0);
	}
	
	return 0;
}