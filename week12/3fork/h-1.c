#include "my.h"

int main(){
	pid_t p1,p2,p3;
	int fd1[2],fd2[2];
	char buf1[10],buf2[10],buf3[10];
	int s1,s2,s3,r1,r2,r3;
	int i,num,j;
	long sum=0;
	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));
	pipe(fd1);    //fd[0]--读 ，fd[1]--写
	p1 = fork();
	if(p1<0){
		perror("p1 fork failed.\n");
		return -1;
	}else if(p1 == 0){   //子进程1
		close(fd1[0]);
		num = 0;
		j=0;
		printf("child1\n");
		for(i=0;i<=65535;i++){
			sprintf(buf1,"%d",num);
			write(fd1[1],buf1,sizeof(buf1));
			num++;
		}
		close(fd1[1]);
		exit(0);
	}else{               //父进程
		pipe(fd2);
		p2 = fork();
		if(p2<0){
			perror("p1 fork failed.\n");
			return -1;		
		}else if(p2 == 0){   //子进程2
			close(fd1[1]);
			close(fd2[0]);
			printf("child2\n");
			for(i=0;i<=65535;i++){
				read(fd1[0],buf2,sizeof(buf2));
				sscanf(buf2,"%d",&num);
				printf("%d\n",num);
				sprintf(buf2,"%d",num);
				write(fd2[1],buf2,sizeof(buf2));
			}
			close(fd1[0]);
			close(fd2[1]);
			exit(0);
		}else{               //父进程 
			p3 = fork();
			if(p3<0){
				perror("p1 fork failed.\n");
				return -1;	
			}else if(p3 == 0){    //子进程3
				close(fd2[1]);
				printf("child3\n");	
				for(i=0;i<=65535;i++){
					read(fd2[0],buf3,sizeof(buf3));
					sscanf(buf3,"%d",&num);
					sum = sum + num;
				}
				close(fd2[0]);
				printf("the sum is %ld\n",sum);				
			}else{            //父进程
				printf("parent waiting\n");
				r1 = wait(&s1);
				r2 = wait(&s2);
				r3 = wait(&s3);
				printf("r1=%d,s1=%d,r2=%d,s2=%d,r3=%d,s3=%d",r1,WEXITSTATUS(s1),r2,WEXITSTATUS(s2),r3,WEXITSTATUS(s3));
				return 0;
			}
		}
	}
}
