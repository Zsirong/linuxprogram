#include "my.h"
static void callback1()
{	printf("-------callback1!-------\n");}
static void callback2()
{	printf("-------callback2!-------\n");}
static void __attribute__((constructor)) before_main(void)
{	printf("-------before main------\n");}
static void __attribute__((destructor)) after_main(void)
{	printf("-------after main------\n");}
int main(void){
	atexit(callback1);
	atexit(callback2);
	FILE *fp;
	char buf[] = {"hello world"};
	if((fp = fopen("test.dat","w+"))==NULL)
	{
		perror("failed to create file!\n");
		return -1;	
	}
	if(fputs(buf,fp)==EOF) //把buf数据写入fp文件
	{
		perror("failed to fputs file!\n");
		return -1;		
	}
	printf("test message!\n");
	//exit(0);
	_exit(0);
	//return 0;
}
