#include "my.h"
void fun(void *arg)
{
	printf("worked thread is running. pid = %d\n",getpid());

}

int main()
{
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,(void *(*)())fun,NULL);
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
