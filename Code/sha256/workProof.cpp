#include "stdio.h"
#include "stdlib.h"
#include "sha256.h"
#include "tsQueue.h"
#include "time.h"
#include <string.h>
#include "block.h"

void linkchar(char* s, char* t)//char数组拼接
{
    while (*s != '\0')
    {
        s++;
    }
    while (*t != '\0')
    {
        *s++ = *t++;
    }
    *s = '\0';
}
int getRandom()
{
    int a;
   // srand((unsigned)time(NULL));
    a = rand();
    return a;
}

int calRandomLen(int a)
{
    int len = 0;
    while (a>0)
    {
        len++;
        a = a / 10;
    }
    return len;
}
Status calculateWorkload(BYTE *hash, ts_link_queue* ts)
{

    char *tsSum;
    Transactionsheet e;
    int pos = 1;
    getItem(ts, e,pos);//拿第一个订单
    linkchar(e.launch, e.receive);
    linkchar(e.launch, e.amount);
    tsSum = e.launch;
    //printf("第一次拼接后的字符串:%s\n", tsSum);
    pos++;
    while (pos<5)//交易单不空
    {
        Transactionsheet e;
        getItem(ts, e,pos);//拿到指定位置订单
       // printf("id:%s\n", e.id);
        pos++;
        linkchar(tsSum, e.launch);
        linkchar(tsSum, e.receive);
        linkchar(tsSum, e.amount);
    }

    //printf("拼接交易单后的字符串:%s\n", tsSum);
    int nums = 0;
    while (nums < 1000)
    {
        //取随机数
        int randNum = getRandom();
 /*       printf("randNum=%d\n", randNum);*/
        int randNumlen = calRandomLen(randNum);


        BYTE bs[150];//拼接数组，不能装太大
        //拼接三部分
        int len = randNumlen + SHA256_BLOCK_SIZE + strlen(tsSum);
        for (int i = 0, j = 0, k = 0; i < len; i++)
        {
            if (i < randNumlen)
            {
                bs[randNumlen - i - 1] = randNum % 10;
                randNum = randNum / 10;
            }
            if (i < randNumlen + SHA256_BLOCK_SIZE && i >= randNumlen)
            {
                bs[i] = hash[j];
                j++;
            }
            if (i >= randNumlen + SHA256_BLOCK_SIZE)
            {
                bs[i] = (BYTE)tsSum[k];
                k++;
            }
        }
  /*      printf("连接后的hash值：");
        for (int i = 0; i < len; i++)
        {
            printf("%x", bs[i]);
        }
        printf("\n");*/
        //hash计算
        BYTE buf[SHA256_BLOCK_SIZE];
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, bs, len);
        sha256_final(&ctx, buf);

        //printf("最后计算的hash值：");
        //for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        //{
        //    printf("%x ", buf[i]);
        //}
        //printf("\n");

        if (buf[0] ==0)//前8位为0
        {
           // printf("succeed!\n");
            return 1;
        }
        nums++;
    }
    //printf("failed!\n");
    return 0;
 
    
}