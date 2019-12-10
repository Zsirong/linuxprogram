#include "my.h"
void * threadfun(void *arg)
{
	pthread_exit(NULL);  //不做操作，调用以后就退出
}
int main()
{
	pthread_t tid;
	int i,ret;
	struct timeval tv1,tv2;
	struct timezone tz;
	gettimeofday(&tv1,&tv2);
	for(i=0;i<10000;i++){
		ret = pthread_create(&tid,NULL,threadfun,NULL);
		if(ret != 0) //不为0建立失败
		{
			perror("create thread failed!\n");
			return -1;		
		}
	}
	gettimeofday(&tv1,&tv2);
	printf("runing time is %ld\n",tv2.tv_usec-tv1.tv_usec);
	return 0;
}
