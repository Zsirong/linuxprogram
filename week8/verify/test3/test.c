#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    void *curr_brk, *tmp_brk = NULL;
    printf("Welcome to sbrk example:%d\n", getpid());
    tmp_brk = curr_brk = sbrk(0);   //获得当然brk的地址
    printf("Program Break Location1:%p\n", curr_brk);
    getchar();
    brk(curr_brk+4096); //增加Heap段4KB空间
    curr_brk = sbrk(0);
    printf("Program break Location2:%p\n", curr_brk);
    int* a = (int *)tmp_brk+32; //尝试使用刚刚扩展的内存空间
    *a = 32;
    printf("%d\n", *a); //没有问题
    getchar();
    brk(tmp_brk);   //恢复到原来的brk大小
    curr_brk = sbrk(0);
    printf("Program Break Location3:%p\n", curr_brk);
    getchar();
    printf("%d\n", *a); //产生SIGSEGV，Segmentation Fault
    return 0;
}
