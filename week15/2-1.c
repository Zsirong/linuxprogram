//结果输出，但结果异常

#include "my.h"
int tickets = 100;    //共享变量
void *worker0(void *arg)
{
	while(1)
	{
		if(tickets>0)
		{
			usleep(1000);
			printf("worker0 read ticket : %d\n",tickets--);
		}
		else
		{
			break;
		}
	}
	return NULL;
}
void *worker1(void *arg)
{
	while(1)
	{
		if(tickets>0)
		{
			usleep(1000);
			printf("worker1 read ticket : %d\n",tickets--);
		}
		else
		{
			break;
		}
	}
	return NULL;
}
int main()
{
	pthread_t tid[2];
	int i,ret;

	void *(*pt[2])();       //函数指针数组
	pt[0] = worker0;
	pt[1] = worker1;
	for(i=0;i<2;i++)
	{
		ret = pthread_create(&tid[i],NULL,pt[i],NULL);
		if(ret!=0)
		{
			perror("create thread!\n");
			exit(1);
		}
	}
	for(i=0;i<2;i++)
		pthread_join(tid[i],NULL);
	return 0;
}
