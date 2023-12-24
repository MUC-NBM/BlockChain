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

//一个交易单节点队列节点
typedef struct hash_node
{
    BYTE hashTs[SHA256_BLOCK_SIZE];
    struct hash_node* next;
}hash_node;

//交易单队列
typedef struct
{
    hash_node* front;
    hash_node* rear;
    int size;
}hash_link_queue;

void InitQueueHash(hash_link_queue*& q);//初始化hash队列
Status EnQueueHash(hash_link_queue*& q, BYTE* e);//入队
Status DeQueueHash(hash_link_queue*& q, BYTE* e);//出队
#endif 