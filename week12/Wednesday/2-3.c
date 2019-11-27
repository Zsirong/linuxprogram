#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
int main(int argc ,char *argv[]){
 	int pipefd[2],result; 
	char buf[1024];	
	int flag=0; 
	pid_t pid; 
	result= pipe(pipefd);//创建一个管道 
	if(result==-1){  
		perror("pipe error:");  
		exit(EXIT_FAILURE); 
	} 
	pid=fork();//创建一个子进程 
	if(pid==-1) {  
		perror("fork  error:");  
		exit(EXIT_FAILURE); 
	} else if(pid==0){
		if((close(pipefd[1]))==-1)//close write only read  
		{   
			perror("close write  error:");
			exit(EXIT_FAILURE);  
		}  
		while(1){ //循环读取数据   
			read(pipefd[0],buf,1024);//最多读取1024个字节   
			printf("read from pipe :  %s",buf);   
			if(strcmp(buf,"quit")==0){// if 读取到的字符串是exit 这是父进程会接受到一个终止进程的信号，父进程会回收子进程的资源等   
				exit(EXIT_SUCCESS);   
			}      
		}      
	}else{  //close read only write  
		if((close(pipefd[0]))==-1){   
			perror("close read error:");   	
			exit(EXIT_FAILURE);  
		}  
		while(1)//循环写入内容  
		{    
			waitpid(pid,NULL,WNOHANG);//等待子进程退出   
			if(flag==1)     
				exit(0);   
			scanf("%s",buf);   
			write(pipefd[1],buf,strlen(buf)+1);//具体写多少个字节   
			if(strcmp(buf,"quit")==0){     
				flag=1;    
				sleep(1);//让子进程完全退出。   
			}  
		} 
	} 
	return 1;
}
