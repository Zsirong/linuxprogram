#include "my.h"
void * fun(void *arg)
{
	int TID = syscall(SYS-gettid);	
	//pthread_self();

	printf("worker---%d : gettid return %d\n",TID,TID);
	printf("worker---%d : pthread_self return %p\n",TID,(void*)pthread_self());
	printf("worker---%d : will exit!\n",TID);
	pthread_exit(NULL);
	return NULL;
}

int main()
{
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,fun,NULL);   //第一次派生线程
	if(ret != 0)
	{
		perror("create failed!\n");
		return -1;
	}
	pthread_join(tid,NULL);

	ret = pthread_create(&tid,NULL,fun,NULL);   //第二次派生线程
	if(ret != 0)
	{
		perror("create failed!\n");
		return -1;
	}
	pthread_join(tid,NULL);
	printf("Master %d : All Done\n",getpid());
	return 0;
}
//在多线程编程时，一定要注意顺序，否则结果出现唯一性
