#include "stdio.h"
#include "stdlib.h"
#include "sha256.h"
#include "tsQueue.h"
#include "time.h"
#include <string.h>
#include "block.h"

void linkchar(char* s, char* t)//char����ƴ��
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
    getItem(ts, e,pos);//�õ�һ������
    linkchar(e.launch, e.receive);
    linkchar(e.launch, e.amount);
    tsSum = e.launch;
    //printf("��һ��ƴ�Ӻ���ַ���:%s\n", tsSum);
    pos++;
    while (pos<5)//���׵�����
    {
        Transactionsheet e;
        getItem(ts, e,pos);//�õ�ָ��λ�ö���
       // printf("id:%s\n", e.id);
        pos++;
        linkchar(tsSum, e.launch);
        linkchar(tsSum, e.receive);
        linkchar(tsSum, e.amount);
    }

    //printf("ƴ�ӽ��׵�����ַ���:%s\n", tsSum);
    int nums = 0;
    while (nums < 1000)
    {
        //ȡ�����
        int randNum = getRandom();
 /*       printf("randNum=%d\n", randNum);*/
        int randNumlen = calRandomLen(randNum);


        BYTE bs[150];//ƴ�����飬����װ̫��
        //ƴ��������
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
  /*      printf("���Ӻ��hashֵ��");
        for (int i = 0; i < len; i++)
        {
            printf("%x", bs[i]);
        }
        printf("\n");*/
        //hash����
        BYTE buf[SHA256_BLOCK_SIZE];
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, bs, len);
        sha256_final(&ctx, buf);

        //printf("�������hashֵ��");
        //for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        //{
        //    printf("%x ", buf[i]);
        //}
        //printf("\n");

        if (buf[0] ==0)//ǰ8λΪ0
        {
           // printf("succeed!\n");
            return 1;
        }
        nums++;
    }
    //printf("failed!\n");
    return 0;
 
    
}