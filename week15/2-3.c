//两线程严格交替进行

#include "my.h"
int tickets = 100;    //共享变量
sem_t empty,full;
void *worker0(void *arg)
{
	while(1)
	{
		sem_wait(&empty);   //p原语
		if(tickets>0)   //读
		{
			usleep(1000);
			printf("worker0 read ticket : %d\n",tickets);   //写
			tickets--;
			sem_post(&full);    //v原语		
		}
		else
		{
			sem_post(&full);    //v原语	
			break;
		}
		pthread_yield();//使两者交替进行
	}
	return NULL;
}
void *worker1(void *arg)
{
	while(1)
	{
		sem_wait(&full);   //p原语
		if(tickets>0)
		{
			usleep(1000);
			printf("worker1 read ticket : %d\n",tickets--);
			sem_post(&empty);    //v原语	
		}
		else
		{
			sem_post(&empty);    //v原语	
			break;
		}
		pthread_yield();//使两者交替进行
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
	
	ret = sem_init(&empty,0,1);    //初始化，同步信号量
	ret = sem_init(&full,0,0);

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
