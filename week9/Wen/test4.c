#include "my.h"
int main(int argc,char *argv[])
{
	printf("test4:pid = %d,ppid = %d\n",getpid(),getppid());
	for(int i=0;i<argc;i++)
		printf("test4:%d : %s\n",i,argv[i]);
	printf("---------------test4 end---------------\n");
	return 0;
}
