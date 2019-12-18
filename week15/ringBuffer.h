#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 16  //缓冲区长度



typedef unsigned char u8;
typedef unsigned int u32;

void initRingbuffer(void);
int wirteRingbuffer(u8* buffer,u32 len);
int readRingbuffer(u8* buffer,u32 len);
u32 getRingbufferValidLen(void);
void releaseRingbuffer(void);

