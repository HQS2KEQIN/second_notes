#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
char str[100] = "helloworld";
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
void *fun(void *sem)
{

	pthread_mutex_lock(&fastmutex);
	for(int i = 0;str[i]!='\0';i++)
	{
		
		fprintf(stderr,"%c",str[i]);
		
		uleep(1000);
	}
	pthread_mutex_unlock(&fastmutex);
	pthread_exit(0);

}


int main()
{
	pthread_t tid1,tid2,tid3,tid4,tid5;
	pthread_create(&tid1,NULL,fun,NULL);
	pthread_create(&tid2,NULL,fun,NULL);
	pthread_create(&tid3,NULL,fun,NULL);
	pthread_create(&tid4,NULL,fun,NULL);
	pthread_create(&tid5,NULL,fun,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
	pthread_mutex_destroy(&fastmutex);
	return 0;
}