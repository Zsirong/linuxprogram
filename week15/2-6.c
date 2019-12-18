//测试环形缓冲区

#include "my.h"
#include "ringBuffer.h"

int main(){
	int a,b;
	a=100;
	initRingbuffer();
	while(1){
		wirteRingbuffer(&a,sizeof(a));
		readRingbuffer(&b,sizeof(b));	
		printf("%d\n",b);
	}
	releaseRingbuffer();
	return 0;
}
