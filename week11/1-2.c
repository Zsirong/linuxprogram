#include "my.h"
int main(){
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("failed fork!\n");
		return -1;
	}
	else if(pid==0){
		printf("child %d is run!\n",getpid());
		printf("child wiil exit!\n");
		while(1);      //让子进程进入无限循环，父进程会先结束
		exit(120);	
	}else{
		printf("parent is waiting child %d to exit!\n ",pid);
		sleep(100);
		printf("parent %d is run!\n",getpid());
		return 0;
	}
}
