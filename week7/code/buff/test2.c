#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

char buf[] = {"write to stdout\n"};
int main(){
	pid_t id;

	if(write(STDOUT_FILENO,buf,sizeof(buf) - 1) != sizeof(buf)-1)
		perror("can't write");
	printf("printf");   //行缓冲
	id = fork();
	if(id < 0)
	 	perror("fork error");
	exit(0);
}
