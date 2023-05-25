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
	int ret ;
	while(1)
	{
		bzero(&msg,sizeof(msg));
		msgrcv(id,&msg,sizeof(msg.text),msg.textype,0);
		if(msg.textype == 1)
		{
			FILE *file = fopen("1.txt","a+");
			fprintf(file,"%s\n",msg.text);
			fclose(file); 
			continue;
		}
		if(!strcmp(msg.text,"quit"))
			break;
		printf("接收到: %s\n",msg.text);

	}

	return 0;
	
}