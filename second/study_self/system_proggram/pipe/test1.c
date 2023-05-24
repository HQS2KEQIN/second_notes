#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int pip[2];
	pipe(pip);
	pid_t x = fork();
	
	
	if(x>0)
	{
		while(1)
		{
			char str_write[30] = {0};
			printf("我是父进程,我要进行输入\n我输入:");
			scanf("%s",str_write);
			write(pip[1],str_write,strlen(str_write));
			sleep(1);
			if(strcmp(str_write,"quit") == 0)
				break;
		}
		wait(NULL);
	}
	if(x == 0)
	{
		while(1)
		{
			char str_read[30] = {0};
			read(pip[0],str_read,sizeof(str_read));
			if(strcmp(str_read,"quit")==0)
			{
				printf("拜拜了,我要变成僵尸\n");
				break;
			}
			printf("我是子进程,我读到了:%s\n",str_read);		
		}	
		exit(0);		
	}
		
	return 0;
}