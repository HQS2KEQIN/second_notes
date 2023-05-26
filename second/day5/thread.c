#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
void *func1(void *arg)
{
	
	int x;
	
	printf("我是子线程1\n");
	for(x = 1;x<10;x++)
	{
		printf("x = %d\n",x);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *func2(void *arg)
{
	
	int x;
	
	printf("我是子线程2\n");
	for(x = 1;x<10;x++)
	{
		printf("y = %d\n",x);
		sleep(1);
	}
	pthread_exit(NULL);
}

pthread_attr_t detachp(int priv)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr,SCHED_RR);
	struct sched_param param = {priv};
	pthread_attr_setschedparam(&attr,&param);
	
	return attr;
}

int main()
{
	pthread_attr_t attr1 = detachp(10);
	pthread_attr_t attr2 = detachp(30);
	pthread_t tid1,tid2;
	
	pthread_create(&tid1,&attr1,func1,NULL);
	pthread_create(&tid2,&attr2,func2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("我完成了\n");
	
	
	
	
	
	return 0;
}