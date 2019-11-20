#include "my.h"
int main()
{
	FILE *fp;
	int pid1,pid2,pid3,status,rv;
	int i;
	if((fp = fopen("out.dat","w+")) == NULL){
		perror("file failed!\n");
		return -1;	
	}
	pid1=fork();
	if(pid1<0)
	{
		perror("foke failed!\n");
		return -1;
	}
	else if(pid1==0)    //1子进程
	{
		printf("child1 pid=%d\n",getpid());
		for(i=0;i<=9;i++){
			fprintf(fp,"1:pid = %d , %d\n",getpid(),i);		
		}
		sleep(3);
		exit(18);
	}else{
		printf("parent fork child2!\n");
		pid2=fork();
		if(pid2 < 0){
			perror("foke failed!\n");
			return -1;
		}else if(pid2==0)    //2子进程
		{
			printf("child2 pid=%d\n",getpid());
			for(i=0;i<=9;i++){
				fprintf(fp,"2:pid = %d , %d\n",getpid(),i);		
			}
			sleep(5);
			exit(99);
		}else{
			printf("parent fork child3!\n");
			pid3=fork();
			if(pid3<0){
				perror("foke failed!\n");
				return -1;
			}else if(pid3==0)    //3子进程
			{
				printf("child3 pid=%d\n",getpid());
				for(i=0;i<=9;i++){
					fprintf(fp,"3:pid = %d , %d\n",getpid(),i);		
				}
				sleep(2);
				exit(108);
			}
			else
			{
				printf("parent waiting child end!\n");
				rv=wait(&status);
				printf("1:child %d end , exit code is %d!\n",rv,WEXITSTATUS(status));
				rv = 0;
				status = 0;		
				rv=waitpid(pid1,&status,0);
				printf("2:child %d end , exit code is %d!\n",rv,WEXITSTATUS(status));
				rv = 0;
				status = 0;		
				rv=waitpid(pid2,&status,WNOHANG);
				printf("3:child %d end , exit code is %d!\n",rv,WEXITSTATUS(status));
				fclose(fp);
				return 0;
			}
		}
	}
	
	
}

