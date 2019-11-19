/*   守护进程   */
#include "my.h"
#include <time.h>
void inint_daemon(void);
int main()
{
	FILE *fp;
	time_t t;	
	inint_daemon();
	while(1){
		sleep(10);
		if((fp=fopen("1-6.log","a")) >=0){
			t=time(0);
			fprintf(fp,"守护进程还在运行，时间是  %s",asctime(localtime(&t)));
			fclose(fp);		
		}
	}
}
