#include "my.h"
void * fun(void *arg)
{
	int k = (int)arg;
	printf("worker---%d : pthread_self return %p\n",k,(void*)pthread_self());
	pthread_exit(NULL);
	return NULL;
}

int main()
{
	pthread_t tid[NUM];
	int ret[NUM],i;
	for(i=0;i<NUM;i++){
		ret[i] = pthread_create(&tid[i],NULL,fun,(void *)i);   //第一次派生线程,将i传入线程,强制类型转换
		if(ret[i] != 0)
		{
			perror("create failed!\n");
			return -1;
		}
		pthread_join(tid[i],NULL);
	}	
	
	printf("Master %d : All Done\n",getpid());
	return 0;
}
//在多线程编程时，一定要注意顺序，否则结果出现唯一性
