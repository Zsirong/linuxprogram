#include "my.h"
int main()
{
	//char *arg[] = {"./test1","123","456","789",NULL};
	printf("caller5 pid = %d ,ppid = %d\n",getpid(),getppid());
	execlp("test1","./test1","123","456","789",NULL);	
	//execv("/home/rlk/linuxprogram/week9/test1",arg);
	printf("execl after calling!\n");
	return 0;
}
