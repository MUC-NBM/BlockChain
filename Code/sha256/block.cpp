#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "block.h"
#include "hashQueue.h"

void getTsBydir(BlockNode* b,ts_link_queue* q)
{
    InitQueueHash(b->hashSum);//��ʼ��hash����
    InitQueue(b->ts); //��ʼ�����׵�����
    while (q->size > 0)
    {
        Transactionsheet t;
        DeQueue(q, t);//��ʼ�����׵���ֱ�Ӵ�ֵ����
        EnQueue(b->ts, t);//�����׵����м��뵽���齻�׵�
    }
  //  printf("length is %d\n", b->ts->size);
}
void showBlock(BlockNode*& b)
{
    BlockNode* r;
    r = b;
    int k = 1;
    printf("��%d������hash��",k);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        printf("%x", r->hash[i]);
    }
    printf("\n");
    while (r->previous!=NULL)
    {
        r = r->previous;
        k++;
        printf("��%d������hash��", k);
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        {
            printf("%x", r->hash[i]);
        }
        printf("\n");
    }
}
void getTs(BlockNode* b)//��ʼ�����齻�׵�
{
    InitQueueHash(b->hashSum);//��ʼ��hash����
    InitQueue(b->ts); //��ʼ�����׵�����

    for (int i = 0; i < 4; i++) //װ�������׵�
    {
        Transactionsheet t;
        initTs(&t,i);//��ʼ�����׵������û�����
        EnQueue(b->ts, t);//���뽻�׵������׵�����
    }

   // printf("length is %d\n", b->ts->size);
}

void getHash(BlockNode* b)//���׵�תhash
{
    int pos = 1;
    while (pos<5)//���׵�����
    {
        Transactionsheet e;
        getItem(b->ts, e,pos);//�������鶩������
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
        
        
        EnQueueHash(b->hashSum, buf);//���

       /* printf("%hhu", bu);*/
    //    break;
    }

}
void calHash(BlockNode* b)//��������Hash
{
    while (b->hashSum->size>1)//hash���г��ȴ���1����ϲ�
    {
        BYTE c1[SHA256_BLOCK_SIZE];
        DeQueueHash(b->hashSum, c1); //ȡ��һ��hash
        BYTE c2[SHA256_BLOCK_SIZE];
        DeQueueHash(b->hashSum, c2); //ȡ�ڶ���hash

        int len = SHA256_BLOCK_SIZE + SHA256_BLOCK_SIZE;
        BYTE bs[64];
        //ƴ��������ϣֵ
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
        //printf("���Ӻ��hashֵ��");
        //for (int i = 0; i < len; i++)
        //{
        //    printf("%x", bs[i]);
        //}
        //printf("\n");
        //����hash���м��ܼ���
        BYTE buf[SHA256_BLOCK_SIZE];
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, bs, len);
        sha256_final(&ctx, buf);
        //������к���
        EnQueueHash(b->hashSum, buf);
    }

    ////���������������hash���浽����hash������
    BYTE bbs[SHA256_BLOCK_SIZE];
  //  printf("hash���г��ȷ���ǰ=%d\n", b->hashSum->size);
    DeQueueHash(b->hashSum, bbs);
    memcpy(b->hash,bbs, SHA256_BLOCK_SIZE);
}
void InitBlockChain3(BlockNode*& oneBlock, FILE* fpRead)
{
    Transactionsheet t;
    oneBlock = (BlockNode*)malloc(sizeof(BlockNode));//����ռ�
    InitQueueHash(oneBlock->hashSum);//��ʼ��hash����
    InitQueue(oneBlock->ts); //��ʼ�����׵�����
    for (int i = 0; i < 4; i++) //�ĸ����׵�
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
        //initTs(&t, i);//��ʼ�����׵������û�����
        EnQueue(oneBlock->ts, t);//���뽻�׵������׵�����
    }
    getHash(oneBlock);//����תhash
    //printf("hash���г��ȼ���ǰ=%d\n", b.hashSum->size);
    calHash(oneBlock);//��������hash
    //printf("����hash�ǣ�\n");
    //for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    //{
    //    printf("%x", oneBlock->hash[i]);
    //}
    //printf("\n");
    oneBlock->previous = NULL;//�ÿ�
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
    while (pos < 5)//���׵�����
    {
        Transactionsheet e;
        getItem(s->ts, e, pos);//�õ�ָ��λ�ö���
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
    oneBlock = (BlockNode*)malloc(sizeof(BlockNode));//����ռ�
    getTsBydir(oneBlock, q);
    getHash(oneBlock);//����תhash
////printf("hash���г��ȼ���ǰ=%d\n", b.hashSum->size);
    calHash(oneBlock);//��������hash
    printf("����hash�ǣ�\n");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        printf("%x", oneBlock->hash[i]);
    }
    printf("\n");
    oneBlock->previous = NULL;//�ÿ�

}
void getPreviousHash(BlockNode*& orginalBlock, BYTE* oneHash)
{
    BlockNode* r;
    r = orginalBlock;
    while (r->previous!=NULL)//ָ����ĩ������
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
    //�������һ����hash���Ը�ֵ
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
    //Ĭ��������һ������
    while (pos < 5)
    {
        Transactionsheet e;
        getItem(s->ts, e, pos);//�õ�ָ��λ�ö���
        pos++;
        /*printf("id:%s\n", e.id);*/
        fputs(e.id, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.launch, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.receive, fpWrite);
        fputs(" ", fpWrite);
        fputs(e.amount, fpWrite);
        if(pos<5)//���һ�в�Ҫ�س�
        fputs("\n", fpWrite);
    }
    //fclose(fpWrite);
    while (s->previous!=NULL)
    {
        s = s->previous;
        //FILE* fpWrite = fopen("1.txt", "w");
        int pos = 1;
        fputs("\n", fpWrite);
        while (pos < 5)//���׵�����
        {
            Transactionsheet e;
            getItem(s->ts, e, pos);//�õ�ָ��λ�ö���
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