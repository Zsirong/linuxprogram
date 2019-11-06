#include "my.h"
static void __attribute__((constructor)) before_main()
{
	printf("------------------before main------------\n");
}
static void __attribute__((destructor)) after_main()
{
	printf("----------------after main---------------\n");
}
static void callback1(void){printf("----callback1\n");}//回调函数
static void callback2(void){printf("----callback2\n");}//回调函数
static void callback3(void){printf("----callback3\n");}//回调函数
int main(){
	atexit(callback1);
	atexit(callback2);
	atexit(callback3);
	printf("main\n");
	return 0;
}
