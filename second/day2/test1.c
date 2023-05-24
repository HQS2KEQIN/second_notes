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
	int open_file = open("1.txt",O_RDWR);
	printf("%d\n",open_file);
	return 0;;
	
}