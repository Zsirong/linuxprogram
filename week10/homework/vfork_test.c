#include "my.h"

int main(){
	FILE *fp;
	int i;
	pid_t pid;
	char buf1[] = {"abcdef"};
	char buf2[] = {"123456"};
	if((fp = fopen("vfork_test.dat","a+"))==NULL)
	{
		perror("failed to create file!\n");
		return -1;	
	}
	pid = vfork();
	if(pid<0)
	{
		perror("vfork dailed!\n");
		exit(-1);	
	}else if(pid == 0){  //子进程
		//for(i=0;i<9;i++)
		//	fprintf(fp,"%d",i);	
		fputs(buf1,fp);
		exit(0);
	}else{               //父进程
		//for(i=0;i<9;i++)
		//	fprintf(fp,"%d",i);	
		fputs(buf2,fp);
		exit(0);
	}
	return 0;
}
