#include "my.h"
#include <wait.h>

int a[100]={0};
int g=99;
int main(){
	int l=99;
	static int s = 20;
	for(int i=0;i<10;i++)
		printf("%d : %d\n",getpid(),i);
	return 0;
}
