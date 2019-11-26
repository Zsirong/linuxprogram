#include "my.h"
int main()
{
	pid_t p;
	int fd[2],wn,rn;
	char r_buf[30],w_buf[30];
	memset(r_buf,0,sizeof(r_buf));
	memset(w_buf,0,sizeof(w_buf));
	pipe(fd);     //fd[0]--读 ，fd[1]--写
	p=fork();
	if(p<0){
		perror("fork failed.\n");
		return -1;
	}else if(p==0){
		close(fd[0]);
		sprintf(w_buf,"[child %d] is running.\n",getpid());
		while(1){
			wn = write(fd[1],w_buf,sizeof(w_buf));
			printf("[child] write to pipe %d byte.\n",wn);
			if(wn==-1){
				printf("[child] write error.\n");
				break;
			}		
		}
		close(fd[1]);
		exit(0);
	}else{
		close(fd[1]);    //关闭写管道
		while(1){
			rn = read(fd[0],r_buf,sizeof(r_buf));
			printf("[child] read from pipe %d byte. Conten of pipe is %s\n",rn,r_buf);
			if(rn==0){
				printf("[parent] read error.\n");
				break;
			}		
		}
		close(fd[0]);
		return 0;
	}
}
