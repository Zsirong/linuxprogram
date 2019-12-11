#include "my.h"
int run_now=1;
void *thread_function(void *arg)
{
	int print_count2=0;
	while(print_count2++<5){
		if(run_now==2)
		{
			printf("function is running!\n");
			run_now = 1;		
		}else{
			printf("function is sleeping!\n");
			sleep(1);
		}
	}
	pthread_exit(NULL);
}
int main(){
	int print_count1=1;
	pthread_t tid;
	if(pthread_create(&tid,NULL,thread_function,NULL)!=0)
	{
		perror("thread createion failed!\n");
		exit(1);
	}
	while(print_count1++<5)
	{
		if(run_now==1){
			printf("main thread is running!\n");
			run_now = 2;
		}else{
			printf("main thread is sleeping!\n");
			sleep(1);
		}
	}
	pthread_join(tid,NULL);
	exit(0);
}
