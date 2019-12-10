#include "my.h"
void sigfun(int signo){
	switch(signo)
	{
		case 1:
			printf("Catch SIGHUP\n");	
			signal(1,SIG_DFL);
			break;
		case 2:
			printf("Catch SIGINT\n");	
			break;
		case 3:
			printf("Catch QUIT\n");	
			break;
	}
}
int main()
{
	signal(1,sigfun);
	signal(2,sigfun);	
	signal(3,sigfun);
	printf("test pid [%d]\n",getpid());
	while(1);
	//signal(1,SIG_DFL);
	return 0;
}
