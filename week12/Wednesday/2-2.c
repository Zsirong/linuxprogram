#include "my.h"

int main()
{
	int fd[2];    //fd[0]-->读  ,fd[1]-->写
	pid_t pid;
	if(signal(SIGPIPE,sighandler)==SIG_ERR)
	{
		fprintf(stderr,"signal error [%s]\n",strerror(errno));
		return -3;
	}
	if(pipe(fd) == -1){
		fprintf(stderr,"create pipe error. reason:[%s]\n",strerror(errno));
		return -1;
	}

	pid = fork();
	if(pid <0){
		fprintf(stderr,"create child error. reason:[%s]\n",strerror(errno));
		return -2;	
	}else if(pid == 0){
		printf("[child]: pid = %d,ppid = %d\n",getpid(),getppid());
		close(fd[0]);
		
		exit(0);	
	}else{
		close(fd[0]);
		wait(NULL);
		int ret;
		ret = write(fd[1],"hello",5);    //发送信号
		if(ret == -1){
			printf("[parent]: write failed! error reason :[%s]\n",strerror(errno));
		}
		return 0;
	}
}

void sighandler(int signo)
{
	printf("[parent]: parent catch a SIGPIPE signal and signumber = %d\n",signo);
}

