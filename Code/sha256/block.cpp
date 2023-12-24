#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "block.h"
#include "hashQueue.h"

void getTsBydir(BlockNode* b,ts_link_queue* q)
{
    InitQueueHash(b->hashSum);//初始化hash队列
    InitQueue(b->ts); //初始化交易单队列
    while (q->size > 0)
    {
        Transactionsheet t;
        DeQueue(q, t);//初始化交易单，直接传值进来
        EnQueue(b->ts, t);//将交易单队列加入到区块交易单
    }
  //  printf("length is %d\n", b->ts->size);
}
void showBlock(BlockNode*& b)
{
    BlockNode* r;
    r = b;
    int k = 1;
    printf("第%d个区块hash：",k);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        printf("%x", r->hash[i]);
    }
    printf("\n");
    while (r->previous!=NULL)
    {
        r = r->previous;
        k++;
        printf("第%d个区块hash：", k);
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        {
            printf("%x", r->hash[i]);
        }
        printf("\n");
    }
}
void getTs(BlockNode* b)//初始化区块交易单
{
    InitQueueHash(b->hashSum);//初始化hash队列
    InitQueue(b->ts); //初始化交易单队列

    for (int i = 0; i < 4; i++) //装三个交易单
    {
        Transactionsheet t;
        initTs(&t,i);//初始化交易单，由用户输入
        EnQueue(b->ts, t);//加入交易单到交易单队列
    }

   // printf("length is %d\n", b->ts->size);
}

void getHash(BlockNode* b)//交易单转hash
{
    int pos = 1;
    while (pos<5)//交易单不空
    {
        Transactionsheet e;
        getItem(b->ts, e,pos);//遍历区块订单队列
        pos++;
        int len1 = strlen(e.launch) + strlen(e.receive)+1;
        strcat_s(e.launch,len1,e.receive);
        int len2 = strlen(e.launch) + strlen(e.amount)+1;
        strcat_s(e.launch,len2,e.amount);

        BYTE buf[SHA256_BLOCK_SIZE];
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,(BYTE*)e.launch, strlen(e.launch));
        sha256_final(&ctx,buf);
        
        
        EnQueueHash(b->hashSum, buf);//入队

       /* printf("%hhu", bu);*/
    //    break;
    }

}
void calHash(BlockNode* b)//计算区块Hash
{
    while (b->hashSum->size>1)//hash队列长度大于1，则合并
    {
        BYTE c1[SHA256_BLOCK_SIZE];
        DeQueueHash(b->hashSum, c1); //取第一个hash
        BYTE c2[SHA256_BLOCK_SIZE];
        DeQueueHash(b->hashSum, c2); //取第二个hash

        int len = SHA256_BLOCK_SIZE + SHA256_BLOCK_SIZE;
        BYTE bs[64];
        //拼接两个哈希值
        for (int i = 0,j=0; i < len; i++)
        {
            if (i < 32)
            {
                bs[i] = c1[i];
            }
            else
            {
                bs[i] = c2[j];
                j++;
            }
        }
        //printf("连接后的hash值：");
        //for (int i = 0; i < len; i++)
        //{
        //    printf("%x", bs[i]);
        //}
        //printf("\n");
        //两两hash进行加密计算
        BYTE buf[SHA256_BLOCK_SIZE];
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, bs, len);
        sha256_final(&ctx, buf);
        //放入队列后面
        EnQueueHash(b->hashSum, buf);
    }

    ////将计算出来的区块hash保存到区块hash属性中
    BYTE bbs[SHA256_BLOCK_SIZE];
  //  printf("hash队列长度放入前=%d\n", b->hashSum->size);
    DeQueueHash(b->hashSum, bbs);
    memcpy(b->hash,bbs, SHA256_BLOCK_SIZE);
}
void InitBlockChain3(BlockNode*& oneBlock, FILE* fpRead)
{
    Transactionsheet t;
    oneBlock = (BlockNode*)malloc(sizeof(BlockNode));//分配空间
    InitQueueHash(oneBlock->hashSum);//初始化hash队列
    InitQueue(oneBlock->ts); //初始化交易单队列
    for (int i = 0; i < 4; i++) //四个交易单
    {
        fgets(t.id, 8, fpRead);
        //printf("id:%s\n", t.id);
        getc(fpRead);
        fgets(t.launch, 8, fpRead);
        //printf("launch:%s\n", t.launch);
        getc(fpRead);
        fgets(t.receive, 8, fpRead);
        //printf("receive:%s\n", t.receive);
        getc(fpRead);
        fgets(t.amount, 8, fpRead);
        //printf("amount:%s\n", t.amount);
        getc(fpRead);
        /*getc(fpRead);*/
        //initTs(&t, i);//初始化交易单，由用户输入
        EnQueue(oneBlock->ts, t);//加入交易单到交易单队列
    }
    getHash(oneBlock);//订单转hash
    //printf("hash队列长度计算前=%d\n", b.hashSum->size);
    calHash(oneBlock);//计算区块hash
    //printf("区块hash是：\n");
    //for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    //{
    //    printf("%x", oneBlock->hash[i]);
    //}
    //printf("\n");
    oneBlock->previous = NULL;//置空
}
void writeNewBlock(BlockNode* b,int flag)
{
    FILE* fpWrite;
    BlockNode* s = b;
    if (flag == 1)
    {
        fpWrite = fopen("new1.txt", "w");
    }
    else if (flag == 2)
    {
        fpWrite = fopen("new2.txt", "w");
    }
    else
    {
        fpWrite = fopen("new3.txt", "w");
    }
    int pos = 1;
    while (pos < 5)//交易单不空
    {
        Transactionsheet e;
        getItem(s->ts, e, pos);//拿到指定位置订单
        pos++;
        /*printf("id:%s\n", e.id);*/
        fputs(e.id, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.launch, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.receive, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.amount, fpWrite);
        if(pos<5)
        fputs("\n", fpWrite);
    }
    fclose(fpWrite);
}
void InitBlockChain(BlockNode*& oneBlock,ts_link_queue *q)
{
    oneBlock = (BlockNode*)malloc(sizeof(BlockNode));//分配空间
    getTsBydir(oneBlock, q);
    getHash(oneBlock);//订单转hash
////printf("hash队列长度计算前=%d\n", b.hashSum->size);
    calHash(oneBlock);//计算区块hash
    printf("区块hash是：\n");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        printf("%x", oneBlock->hash[i]);
    }
    printf("\n");
    oneBlock->previous = NULL;//置空

}
void getPreviousHash(BlockNode*& orginalBlock, BYTE* oneHash)
{
    BlockNode* r;
    r = orginalBlock;
    while (r->previous!=NULL)//指向最末端区块
    {
        r = r->previous;
    }
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        oneHash[i] = r->hash[i];
    }

}
int getLength(BlockNode*& b)
{
    int i = 1;
    BlockNode* r;
    r = b;
    while (r->previous!=NULL)
    {
        r = r->previous;
        i++;
    }
    return i;
}
void addBlockChain(BlockNode*& orginalBlock, BlockNode*& newBlock)
{
    BlockNode* s;
    s = orginalBlock;
    while (s->previous!=NULL)
    {
        s = s->previous;
    }
    //区块的上一区块hash属性赋值
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        newBlock->priorHash[i] = s->hash[i];
    }
    s->previous = newBlock;
}
void writeToLocalFile(BlockNode* b,int flag)
{
    BlockNode* s=b;
    FILE* fpWrite;
    if(flag==1)
        fpWrite = fopen("1.txt", "w");
    else if (flag == 2)
        fpWrite = fopen("2.txt", "w");
    else
        fpWrite = fopen("3.txt", "w");
    int pos = 1;
    //默认至少有一个区块
    while (pos < 5)
    {
        Transactionsheet e;
        getItem(s->ts, e, pos);//拿到指定位置订单
        pos++;
        /*printf("id:%s\n", e.id);*/
        fputs(e.id, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.launch, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.receive, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.amount, fpWrite);
        if(pos<5)//最后一行不要回车
        fputs("\n", fpWrite);
    }
    //fclose(fpWrite);
    while (s->previous!=NULL)
    {
        s = s->previous;
        //FILE* fpWrite = fopen("1.txt", "w");
        int pos = 1;
        fputs("\n", fpWrite);
        while (pos < 5)//交易单不空
        {
            Transactionsheet e;
            getItem(s->ts, e, pos);//拿到指定位置订单
            pos++;
            /*printf("id:%s\n", e.id);*/
            fputs(e.id, fpWrite);
            fputs(" ", fpWrite);
            fputs(e.launch, fpWrite);
            fputs(" ", fpWrite);
            fputs(e.receive, fpWrite);
            fputs(" ", fpWrite);
            fputs(e.amount, fpWrite);
            if(pos<5)
            fputs("\n", fpWrite);
        }
    }
    fclose(fpWrite);

}