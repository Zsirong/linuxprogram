#include "my.h"
int arg = 0;
void foo(void *v)
{
	int n=(int )v;
	int *pt;
	pt = (int *)malloc(sizeof(int));
	int sum = 0;
	arg++;
	printf("%d : global arg = %d\n",n,arg);
	int arg;
	arg = (n+1)*100;
	printf("%d : local arg = %d\n",n,arg);
	for(int i=0;i<arg;i++)
		sum = sum+i;
	*pt = sum;
	pthread_exit((void *)pt);
}
int main()
{
	pthread_t tid[NUM];
	int rev[NUM];
	int **rst;
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
		printf("master %d: sum = %d\n",i,*rst);
	}
}
