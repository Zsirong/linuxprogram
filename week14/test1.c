#include "my.h"
int i=0;
void func()
{
	int buffer[256];
	printf("i=%d\n",i);
	i++;
	func();
}
int main()
{
	func();
	sleep(10);
}
