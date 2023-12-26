#pragma once
#ifndef TSQUEUE_H
#define TEQUEUE_H

#include <stdlib.h>
#include "stdio.h"

typedef int Status;
//���׵�
typedef struct Transactionsheet
{
    char id[8]; //���׵���
    char launch[100]; //���𷽹�Կ
    char receive[8];    //���շ���Կ
    char amount[8];     //��������
}Transactionsheet;
void initTs(Transactionsheet* t, int i);
//���׵����нڵ�
typedef struct ts_node
{
    Transactionsheet ts;
    struct ts_node* next;
}ts_node;

//���׵�����
typedef struct ts_link_queue
{
    ts_node* front;
    ts_node* rear;
    int size;
}ts_link_queue;

void InitQueue(ts_link_queue *&q);//��ʼ�����׵�����
Status EnQueue(ts_link_queue *&q, Transactionsheet e);//���
Status DeQueue(ts_link_queue *&q, Transactionsheet& e);//����
Status getItem(ts_link_queue* q, Transactionsheet& e, int pos);//��ȡָ��Ԫ��
#endif 