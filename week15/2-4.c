//生产消费者
//一个向缓冲区写100，一个从缓冲区读100
//互斥，生产消费者互斥使用环形缓冲区，mutex=1，互斥信号量mutex
//合作，生产->产品->消费-->product=0，消费->空间->生产-->space=5，同步信号量sem_t
//生产者（p(space)->p(mutex)->/*生产*/->v(mutex)->v(product)）
//消费者（p(product)->p(mutex)->/*消费*/->v(mutex)->v(space)）


//写了大致格式，缓冲区没用上

#include "my.h"
int tickets = 100;    //共享变量
pthread_mutex_t mutex;
sem_t space,product;
void *worker0(void *arg)   //生产者
{
	while(1)
	{
		sem_wait(&space);   //p原语
		pthread_mutex_lock(&mutex);    //加锁
		if(tickets>0)   //读
		{
			//usleep(1000);
			printf("productor read ticket : %d\n",tickets);   //写
			tickets--;
			pthread_mutex_unlock(&mutex);    //解锁
			sem_post(&product);    //v原语		
		}
		else
		{
			sem_post(&product);    //v原语	
			break;
		}
		pthread_yield();//使两者交替进行
	}
	return NULL;
}
void *worker1(void *arg)     //消费者
{
	while(1)
	{
		sem_wait(&product);   //p原语
		pthread_mutex_lock(&mutex);    //加锁
		if(tickets>0)
		{
			//usleep(1000);
			printf("buyyer read ticket : %d\n",tickets--);
			pthread_mutex_unlock(&mutex);    //解锁
			sem_post(&space);    //v原语	
		}
		else
		{
			sem_post(&space);    //v原语	
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
	pthread_mutex_init(&mutex,NULL);   //mutex初始化
	ret = sem_init(&space,0,5);    //初始化，同步信号量
	ret = sem_init(&product,0,0);

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
