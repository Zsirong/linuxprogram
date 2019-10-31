#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
    void * addr;
    printf("Welcome to sbrk example:%d\n", getpid());
    getchar();
    //申请4096*2=8KB的空间，地址空间可读写，私有且匿名。
    addr = mmap(NULL, 4096 * 2, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(addr < 0) {
        perror("mmap");
    }
    printf("Program Allocate :%p\n", addr);
    getchar();
    if(munmap(addr, 1024) != 0){
        perror("munmap");
    }
    return 0;
}
