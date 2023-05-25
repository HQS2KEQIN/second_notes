#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

struct megque
{
	long textype;
	char text[100];
};
int main()
{
	key_t key = ftok(".",10);
	int id = msgget(key,IPC_CREAT|0666);
	struct megque msg;
	long resr;
	printf("请输入自己的编号:");
	scanf("%ld",&resr);
	int x = fork();
	if(x>0)
	{
		while(1)
		{
			bzero(msg.text,sizeof(msg.text));
			char text[30] = {0};
			scanf("%s",text);	
			sscanf(text,"%ld:%s",&msg.textype,msg.text);
			msgsnd(id,&msg,strlen(msg.text),0);
			if(!strcmp(msg.text,"quit"))
				break;
		}
	}
	if(x==0)
	{
		while(1)
		{
			bzero(&msg,sizeof(msg));
			msgrcv(id,&msg,sizeof(msg.text),resr,0);
			if(!strcmp(msg.text,"quit"))
				break;
			printf("接收到消息: %s\n",msg.text);

		}
		exit(0);
	}
	return 0;
	
}