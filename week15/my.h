#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <sys/syscall.h>
#define NUM 4
#define LOOP 10000000

typedef struct {
    int s;
    int t;
}result;

#define TN 100
#define WRITER_FIRST
