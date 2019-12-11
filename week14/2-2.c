#include "my.h"
int arg = 0;
void foo(void *v)
{
	int n=(int )v;
	result *pt;
	pt = (result *)malloc(sizeof(result));
	int sum = 0;
	struct timeval tv1,tv2;
	struct timezone tz;
	arg++;
	printf("%d : global arg = %d\n",n,arg);
	int arg;
	arg = (n+1)*10000;
	printf("%d : local arg = %d\n",n,arg);
	gettimeofday(&tv1,&tz);
	for(int i=0;i<arg;i++)
		sum = sum+i;
	gettimeofday(&tv2,&tz);
	pt->s = sum;   //求和
	pt->t = tv2.tv_usec-tv1.tv_usec;   //时间
	printf("sum = %d,time = %d\n",pt->s,pt->t);
	pthread_exit((void *)pt);
}
int main()
{
	pthread_t tid[NUM];
	int rev[NUM];
	result *rst;
	for(int i=0;i<NUM;i++)
	{
		rev[i]=pthread_create(&tid[i],NULL,(void *(*)())foo,(void*)i);
		if(rev[i] != 0)
		{
			perror("thread failed!\n");
			exit -1;
		}
		printf("master %d: arg = %d\n",i,arg);
		pthread_join(tid[i],(void **)&rst);
		printf("master %d: sum = %d , time = %d\n",i,rst->s,rst->t);
	}
}
