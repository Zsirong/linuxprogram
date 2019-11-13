#include "my.h"

int main(){
	FILE *fp;
	int i;
	pid_t pid;
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
	}else if(pid == 1){  //子进程
		for(i=0;i<9;i++)
			fprintf(fp,"%d",i);	
	}else{               //父进程
		for(i=0;i<9;i++)
			fprintf(fp,"%d",i);
	}
	return 0;
}
