#include "my.h"
int main(){
	pid_t pid;
	int r,status;
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
		while((wait(&status))!=-1){
			if(WIFEXITED(status)){
				printf("child %d is finished with exit mode. exit code = %d\n",r,WEXITSTATUS(status));
			}else if(WIFSIGNALED(status)){
				printf("child %d is finished with signal mode. signal code = %d\n",r,WTERMSIG(status));
			}else{
				printf("unknow mode!\n");			
			}	
		}
		//printf("child %d is finished. return code = %d\n",r,WEXITSTATUS(status));
		//sleep(100);
		printf("parent %d is run!\n",getpid());
		return 0;
	}
}
