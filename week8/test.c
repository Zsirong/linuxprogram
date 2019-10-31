#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	printf("ppid = %d,pid = %d\n",getppid(),getpid());
	while(1);
	return 0;
}

