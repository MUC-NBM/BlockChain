#include <stdio.h>
#include <stdlib.h>
#include "tsQueue.h"
#include <string.h>

// ��ʼ��ÿһ�����׵�
void initTs(Transactionsheet* t, int i) {
    printf("-----------��%d�����׵�---------\n", i + 1);
    printf("�����뽻�׵�id��7λ��:");
    scanf("%s", t->id);
    printf("�����뽻�׵����𷽹�Կ��7λ��:");
    scanf("%s", t->launch);
    printf("�����뽻�׵����շ���Կ��7λ��:");
    scanf("%s", t->receive);
    printf("�����뽻�׵��������7λ��:");
    scanf("%s", t->amount);
}

// ��ʼ������
void InitQueue(ts_link_queue*& q) {
    q = (ts_link_queue*)malloc(sizeof(ts_link_queue));
    q->front = q->rear = (ts_node*)malloc(sizeof(ts_node));
    q->size = 0;
    q->front->next = NULL;
}

// ��Ӳ���
Status EnQueue(ts_link_queue*& q, Transactionsheet e) {
    ts_node* s = (ts_node*)malloc(sizeof(ts_node));
    s->ts = e;
    q->size++;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
    return 1;
}

// ���Ӳ���
Status DeQueue(ts_link_queue*& q, Transactionsheet& e) {
    if (q->front == q->rear)
        return 0;
    ts_node* p = q->front->next;
    e = p->ts;
    q->size--;
    q->front->next = p->next;
    if (q->rear == p) {
        q->rear = q->front;
        free(p);
    }
    return 1;
}

// ��ȡ������ָ��λ�õ�Ԫ��
Status getItem(ts_link_queue* q, Transactionsheet& e, int pos) {
    ts_node* r = q->front;
    while (pos > 1) {
        r = r->next;
        pos--;
    }
    ts_node* p = r->next;
    e = p->ts;
    return 1;
}
