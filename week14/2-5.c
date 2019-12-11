#include "my.h"

pthread_rwlock_t rwlock;
int gn=0;
void *work(void *par)
{
	int i;
	pthread_rwlock_rdlock(&rwlock);
	for(i = 0;i<LOOP;i++)
	{
		gn++;
	}	
	pthread_rwlock_unlock(&rwlock);
	return NULL;
}
int main()
{
	pthread_t tid[NUM];
	char err[1024];
	int i,ret;

	ret = pthread_rwlock_init(&rwlock,NULL);
	if(ret)
	{
		fprintf(stderr,"init rw lock failed (%s)\n",strerror_r(ret,err,sizeof(err)));
		exit(1);
	}
	pthread_rwlock_wrlock(&rwlock);
	for(i = 0;i<NUM;i++)
	{
		ret = pthread_create(&tid[i],NULL,work,NULL);
		if(ret !=0 )
		{
			perror("create failed!\n");
			exit(2);
		}
//		pthread_rwlock_unlock(&rwlock);
//		pthread_join(tid[i],NULL);	
//		pthread_rwlock_destroy(&rwlock);
	}
	pthread_rwlock_unlock(&rwlock);
	for(i=0;i<NUM;i++)
	{
		pthread_join(tid[i],NULL);	
	}
	pthread_rwlock_destroy(&rwlock);
	printf("thread number  :%d\n",NUM);
	printf("loop per thread  :%d\n",LOOP);
	printf("expect result  :%d\n",LOOP*NUM);
	printf("actual result  :%d\n",gn);
	return 0;
}
