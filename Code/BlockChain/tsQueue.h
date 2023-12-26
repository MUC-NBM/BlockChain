#pragma once
#ifndef TSQUEUE_H
#define TEQUEUE_H

#include <stdlib.h>
#include "stdio.h"

typedef int Status;
//交易单
typedef struct Transactionsheet
{
    char id[8]; //交易单号
    char launch[100]; //发起方公钥
    char receive[8];    //接收方公钥
    char amount[8];     //交易数额
}Transactionsheet;
void initTs(Transactionsheet* t, int i);
//交易单队列节点
typedef struct ts_node
{
    Transactionsheet ts;
    struct ts_node* next;
}ts_node;

//交易单队列
typedef struct ts_link_queue
{
    ts_node* front;
    ts_node* rear;
    int size;
}ts_link_queue;

void InitQueue(ts_link_queue *&q);//初始化交易单队列
Status EnQueue(ts_link_queue *&q, Transactionsheet e);//入队
Status DeQueue(ts_link_queue *&q, Transactionsheet& e);//出队
Status getItem(ts_link_queue* q, Transactionsheet& e, int pos);//获取指定元素
#endif 