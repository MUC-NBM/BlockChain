#ifndef HASHQUEUE_H
#define HASHQUEUE_H

#include <stdlib.h>
#include "sha256.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

//һ�����׵��ڵ���нڵ�
typedef struct hash_node
{
    BYTE hashTs[SHA256_BLOCK_SIZE];
    struct hash_node* next;
}hash_node;

//���׵�����
typedef struct
{
    hash_node* front;
    hash_node* rear;
    int size;
}hash_link_queue;

void InitQueueHash(hash_link_queue*& q);//��ʼ��hash����
Status EnQueueHash(hash_link_queue*& q, BYTE* e);//���
Status DeQueueHash(hash_link_queue*& q, BYTE* e);//����
#endif 