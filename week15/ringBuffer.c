#include "ringBuffer.h"

static u32 validLen;//已使用的数据长度
static u8* pHead = NULL;//环形存储区的首地址
static u8* pTail = NULL;//环形存储区的结尾地址
static u8* pValid = NULL;//已使用的缓冲区的首地址
static u8* pValidTail = NULL;//已使用的缓冲区的尾地址

/*
 * 初始化环形缓冲区
 * 环形缓冲区这里可以是malloc申请的内存,也可以是Flash存储介质
 * */
void initRingbuffer(void)
{
    if(pHead == NULL)
    {
        pHead = (u8*) malloc(BUFFER_SIZE);
    }
    pValid = pValidTail = pHead;
    pTail = pHead + BUFFER_SIZE;
    validLen = 0;
}

/*
 * function:向缓冲区中写入数据
 * param:@buffer 写入的数据指针
 *       @addLen 写入的数据长度
 * return:-1:写入长度过大
 *        -2:缓冲区没有初始化
 * */
int wirteRingbuffer(u8* buffer,u32 addLen)
{
    if(addLen > BUFFER_SIZE) return -2;
    if(pHead==NULL) return -1;
    assert(buffer);

    //将要存入的数据copy到pValidTail处
    if(pValidTail + addLen > pTail)//需要分成两段copy
    {
        int len1 = pTail - pValidTail;
        int len2 = addLen - len1;
        memcpy( pValidTail, buffer, len1);
        memcpy( pHead, buffer + len1, len2);
        pValidTail = pHead + len2;//新的有效数据区结尾指针
    }else
    {
        memcpy( pValidTail, buffer, addLen);
        pValidTail += addLen;//新的有效数据区结尾指针
    }

    //需重新计算已使用区的起始位置
    if(validLen + addLen > BUFFER_SIZE)
    {
        int moveLen = validLen + addLen - BUFFER_SIZE;//有效指针将要移动的长度
        if(pValid + moveLen > pTail)//需要分成两段计算
        {
            int len1 = pTail - pValid;
            int len2 = moveLen - len1;
            pValid = pHead + len2;
        }else
        {
            pValid = pValid + moveLen;
        }
        validLen = BUFFER_SIZE;
    }else
    {
        validLen += addLen;
    }

    return 0;
}

/*
 * function:从缓冲区内取出数据
 * param   :@buffer:接受读取数据的buffer
 *          @len:将要读取的数据的长度
 * return  :-1:没有初始化
 *          >0:实际读取的长度
 * */
int readRingbuffer(u8* buffer,u32 len)
{
    if(pHead==NULL) return -1;

    assert(buffer);

    if(validLen ==0) return 0;

    if( len > validLen) len = validLen;

    if(pValid + len > pTail)//需要分成两段copy
    {
        int len1 = pTail - pValid;
        int len2 = len - len1;
        memcpy( buffer, pValid, len1);//第一段
        memcpy( buffer+len1, pHead, len2);//第二段，绕到整个存储区的开头
        pValid = pHead + len2;//更新已使用缓冲区的起始
    }else
    {
        memcpy( buffer, pValid, len);
        pValid = pValid +len;//更新已使用缓冲区的起始
    }
    validLen -= len;//更新已使用缓冲区的长度

    return len;
}

/*
 * function:获取已使用缓冲区的长度
 * return  :已使用的buffer长度
 * */
u32 getRingbufferValidLen(void)
{
    return validLen;
}

/*
 * function:释放环形缓冲区
 * */
void releaseRingbuffer(void)
{
    if(pHead!=NULL) free(pHead);
    pHead = NULL;
}

