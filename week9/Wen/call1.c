#include "my.h"
int main(){
	char *vector[] = {"test4","111","aaa",NULL};
	printf("call1: pid = %d,ppid = %d\n",getpid(),getppid());
	execvp("test4",vector);//执行test4 test4文件名，vector运行参数指针
	printf("--------after calling----------\n");  //如果没有派生新进程，不会显示
	return 0;
}
