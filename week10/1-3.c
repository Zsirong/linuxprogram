#include "my.h"
#include <wait.h>

int g=10;
int main()
{
	int l=20;
	static int s=30;
	int status;
	pid_t pid;
	//pid = fork();
	pid = vfork();
	if(pid<0)
	{
		//perror("fork dailed!\n");
		perror("vfork dailed!\n");
		return -1;
	}
	else if (pid==0)
	{
		int p=99;
		printf("---------address of var --------\n");
		printf("child pid= %d\n&g = %16p\n&l = %16p\n&s = %16p\n&p=%16p\n",getpid(),&g,&l,&s,&p);
		g=100;
		l=200;
		s=300;
		p=9999;
		execl("./test","test",NULL);
		printf("value in child\n");
		printf("g = %d\nl = %d\ns = %d\np=%d\n",g,l,s,p);
		//return 0;
		//exit(119);
		_exit(0);
	}else{
		//wait(&status);
		//printf("exit code from child is %d\n",WEXITSTATUS(status));
		printf("---------address of var in parent --------\n");
		printf("parent:\n&g = %16p\n&l = %16p\n&s = %16p\n",&g,&l,&s);
		printf("value in parent\n");
		printf("parent : \ng = %d\nl = %d\ns = %d\n",g,l,s);
		return 0;

	}
}
