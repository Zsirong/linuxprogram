#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[],char *env[])
{
	int i=0;
	printf("the First:\n");
	for(;env[i];i++){
		printf("%s\n",env[i]);
	}
	extern char **environ;
	i=0;
	printf("the Second:\n");
	for(;environ[i];i++){
		printf("%s\n",environ[i]);	
	}
	printf("the Third:\n%s\n",getenv("PATH"));
	return 0;
}
