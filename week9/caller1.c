#include "my.h"
int main()
{
	int ret;
	printf("caller1:pid = %d ,ppid = %d\n",getpid(),getppid());
	ret = system("./test1 123 456 hello world");
	printf("After calling! ret = %d\n",ret);
	sleep(10);	
	return 0;
}
