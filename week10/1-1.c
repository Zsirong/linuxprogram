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
	//char buf[] = {"fputs use full buffer!\n"};  //_exit(0)
	char buf[] = {"fputs use full buffer!"};  //exit(0)
	int i;
	if((fp = fopen("test.dat","w+"))==NULL)
	{
		perror("failed to create file!\n");
		return -1;	
	}
	if((fputs(buf,fp))==EOF) //把buf数据写入fp文件
	{
		perror("failed to fputs file!\n");
		return -1;		
	}
	printf("-----------running in main-----------\n");
	//printf("test message!\n");    //默认行缓存,"\n"行缓存的标志,_exit(0)
	printf("test message!");    //exit(0)
	for(i=0;i<1024;i++){
		printf(" ");
	}
	//exit(0);  //无论全缓冲，行缓存printf都能显示，buf也能写入文件
	_exit(0); //无论全缓冲，行缓存buf都无法写入文件（？），但是对于printf，行缓存碰到换行符“\n”显示，全缓冲需要将缓存区填满，才会显示信息。
	//return 0;   //跟exit函数一样效果
}
