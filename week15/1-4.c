//读写锁对于多读少写的程序要高明些

#include "my.h"
static int share=0;
static pthread_rwlock_t rwlock;    //读写锁变量

void *reader(void *param)
{
	int i=(int )param;
	while(1){
		pthread_rwlock_rdlock(&rwlock);   //加读锁
		fprintf(stderr,"reader--%d:the share = %d\n",i,share);
		pthread_rwlock_unlock(&rwlock);  //解锁
	}
	return NULL;
}
void *writer(void *param)
{
	int i=(int )param;
	while(1){
		pthread_rwlock_wrlock(&rwlock);   //加写锁
		share++;
		fprintf(stderr,"writer--%d:the share = %d\n",i,share);
		pthread_rwlock_unlock(&rwlock);  //解锁
		sleep(1);    //睡眠，让读者可以读到share     
	}
	return NULL;
}

int main()
{
	pthread_t tid[TN];
	pthread_rwlockattr_t rwlock_attr;
	pthread_rwlockattr_init(&rwlock_attr);
	#ifdef WRITER_FIRST     //定义写者优先
		pthread_rwlockattr_setkind_np(&rwlock_attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	#endif
	pthread_rwlock_init(&rwlock,&rwlock_attr);
	int i = 0;
	int ret = 0;
	pthread_rwlock_rdlock(&rwlock);
	for(i=0;i<TN;i++)
	{
		if(i%2==0)
		{
			ret = pthread_create(&tid[i],NULL,reader,(void*)i);
		}
		else
		{
			ret = pthread_create(&tid[i],NULL,writer,(void*)i);
		}
		if(ret!=0)
		{
			perror("thread failed!\n");
			exit(1);
		}

	}
	pthread_rwlock_unlock(&rwlock);
	while(i-->0)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_rwlockattr_destroy(&rwlock_attr);
	pthread_rwlock_destroy(&rwlock);
	return 0;
	
}
