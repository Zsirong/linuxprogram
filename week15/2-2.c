//申明共享变量mutex,去掉了结果为0的输出

#include "my.h"
int tickets = 100;    //共享变量
pthread_mutex_t mutex;
void *worker0(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);    //加锁
		if(tickets>0)   //读
		{
			usleep(2000);
			printf("worker0 read ticket : %d\n",tickets--);   //写
			pthread_mutex_unlock(&mutex);    //解锁
		}
		else
		{
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_yield();//让权，释放线程让另一个运行
	}
	return NULL;
}
void *worker1(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);    //加锁
		if(tickets>0)
		{
			usleep(1000);
			printf("worker1 read ticket : %d\n",tickets--);
			pthread_mutex_unlock(&mutex);    //解锁
		}
		else
		{
			pthread_mutex_unlock(&mutex);    //解锁
			break;
		}
		pthread_yield();//让权，释放线程让另一个运行
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
	pthread_mutex_init(&mutex,NULL);   //mutex初始化

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
