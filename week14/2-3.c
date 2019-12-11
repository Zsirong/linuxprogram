#include "my.h"
void *foo(void * arg)
{
	printf("thread is running!\n");
	return (void *)0;
}
int main()
{
	pthread_t tid;
	int ret;
	ret=pthread_create(&tid,NULL,foo,NULL);
	if(ret)
	{
		perror("create failed!\n");
		exit(1);	
	}
	ret = pthread_join(tid,NULL);  //同步，顺序
	//pthread_detach(tid);         //异步，分离
	printf("Master done!\n");
	sleep(5);
	return 0;
}
