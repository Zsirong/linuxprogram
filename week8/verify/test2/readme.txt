rlk@ubuntu:test2$ ./test&   (让程序在后台运行)
[1] 6468
rlk@ubuntu:test2$ a=10,p=0x3bdc4260


[1]+  Stopped                 ./test
rlk@ubuntu:test2$ 
rlk@ubuntu:test2$ ps -u    （查看程序id）
USER        PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
rlk        2891  0.0  0.1  24324  4952 pts/0    Ss   23:22   0:00 bash
rlk        6468  0.0  0.0   4508   720 pts/0    T    23:32   0:00 ./test
rlk        6475  0.0  0.1  41416  3572 pts/0    R+   23:32   0:00 ps -u
rlk@ubuntu:test2$ cat /proc/6468/maps   （输出进程虚拟地址空间的布局）
55a33b712000-55a33b713000 r-xp 00000000 08:01 9443562                    /home/rlk/linuxprogram/week8/verify/test2/test
55a33b912000-55a33b913000 r--p 00000000 08:01 9443562                    /home/rlk/linuxprogram/week8/verify/test2/test
55a33b913000-55a33b914000 rw-p 00001000 08:01 9443562                    /home/rlk/linuxprogram/week8/verify/test2/test
55a33bdc4000-55a33bde5000 rw-p 00000000 00:00 0                          [heap]
7fe3a9034000-7fe3a921b000 r-xp 00000000 08:01 6296186                    /lib/x86_64-linux-gnu/libc-2.27.so
7fe3a921b000-7fe3a941b000 ---p 001e7000 08:01 6296186                    /lib/x86_64-linux-gnu/libc-2.27.so
7fe3a941b000-7fe3a941f000 r--p 001e7000 08:01 6296186                    /lib/x86_64-linux-gnu/libc-2.27.so
7fe3a941f000-7fe3a9421000 rw-p 001eb000 08:01 6296186                    /lib/x86_64-linux-gnu/libc-2.27.so
7fe3a9421000-7fe3a9425000 rw-p 00000000 00:00 0 
7fe3a9425000-7fe3a944c000 r-xp 00000000 08:01 6296158                    /lib/x86_64-linux-gnu/ld-2.27.so
7fe3a9632000-7fe3a9634000 rw-p 00000000 00:00 0 
7fe3a964c000-7fe3a964d000 r--p 00027000 08:01 6296158                    /lib/x86_64-linux-gnu/ld-2.27.so
7fe3a964d000-7fe3a964e000 rw-p 00028000 08:01 6296158                    /lib/x86_64-linux-gnu/ld-2.27.so
7fe3a964e000-7fe3a964f000 rw-p 00000000 00:00 0 
7ffc0bb3c000-7ffc0bb5d000 rw-p 00000000 00:00 0                          [stack]
7ffc0bb66000-7ffc0bb69000 r--p 00000000 00:00 0                          [vvar]
7ffc0bb69000-7ffc0bb6b000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
rlk@ubuntu:test2$ kill 6468   (结束后台运行的进程)

