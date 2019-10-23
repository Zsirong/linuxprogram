#include <stdio.h>
int main(int argc,char *argv[]){
	//int i;
	setvbuf(stdout,NULL,_IONBF,0);	
	printf("hello");
	/*for(i=0;i<1024;i++){
	printf("a");	
	}*/
	while(1);
	return 0;
}
