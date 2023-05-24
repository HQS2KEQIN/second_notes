#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>


int main()
{
	sigset_t *set =(sigset_t*)malloc(sizeof(sigset_t));
	sigemptyset(set);
	int i = 1;
	for(;i<=64;i++)
	{
		if(i == 32||i == 33)
			continue;
		sigaddset(set,i);
		printf("信号%d添加成功\n",i);
	}
	int j = 1;
	sigdelset(set,39);
	for(;j<=64;j++)
	{

		if(j == 32||j == 33)
			continue;
		if(sigismember(set,j)==1)
			printf("信号%d 在集合中\n",j);
		else
		{
			printf("信号%d 不在集合中\n",j);
		}
	}
		
	
	return 0;
	
}