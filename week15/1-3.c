#include "my.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock;
int A[1000];
int B[1000];
int max = 0;

void *fun(void *arg)
{
	int i;
	int h=*(int*)arg;
	pthread_rwlock_rdlock(&rwlock);
	if(!h)
	{
		for(i=0;i<1000;i++)
			A[i]=rand();	
	}else if(h)
	{
		for(i=0;i<1000;i++)
			B[i]=rand();
	}
	if(!h)
	{
		for(i=0;i<1000;i++)
		{
			pthread_mutex_lock(&mutex);
				if(max<A[i])
					max = A[i];
			pthread_mutex_unlock(&mutex);
		}
				
	}else if(h)
	{
		for(i=0;i<1000;i++)
		{
			pthread_mutex_lock(&mutex);
				if(max<B[i])
					max = B[i];
			pthread_mutex_unlock(&mutex);
		}
	}
	pthread_rwlock_unlock(&rwlock);
	return NULL;
}


int main()
{
	pthread_t tid[2];
	int i,ret;
	ret = pthread_rwlock_init(&rwlock,NULL);// 初始化锁
	if(ret)
	{
		perror("rwlock init failed!\n");
		exit(1);
	}
	pthread_rwlock_wrlock(&rwlock);     //
	for(i=0;i<2;i++)
	{
		ret = pthread_create(&tid[i],NULL,fun,(void*)&i);
		if(ret)
		{
			perror("thread init failed!\n");
			exit(2);
		}
	}
	pthread_rwlock_unlock(&rwlock);
	for(i=0;i<2;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&rwlock);
//	printf("thread num ----------------%d\n",NUM);
//	printf("LOOP per thread -----------%d\n",LOOP);
//	printf("expect result -------------%d\n",NUM*LOOP);
//	printf("actual result -------------%d\n",g);
	printf("the biggest number is %d\n",max);
	return 0;
}
