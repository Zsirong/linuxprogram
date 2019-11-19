/*   生成守护进程   */
#include "my.h"

void inint_daemon(void){
	pid_t ch1,ch2;
	int i;
	ch1 = fork();
	if(ch1>0){                 //终止父进程
		exit(0);	
	}else if(ch1 < 0){           //fork失败，退出
		perror("创建子进程失败\n");
		exit(1);
	}
	setsid();                  //在子进程中创建新会话
	chdir("/tmp");             //改变工作目录到"/tmp"
	umask(0);                  //
	for(i=0;i<NOFILE;++i)
	close(i);
	return;
	//exit(0);
}


