#include <stdio.h>
#include <stdlib.h>
#include "tsQueue.h"
#include <string.h>

// 初始化每一个交易单
void initTs(Transactionsheet* t, int i) {
    printf("-----------第%d个交易单---------\n", i + 1);
    printf("请输入交易单id（7位）:");
    scanf("%s", t->id);
    printf("请输入交易单发起方公钥（7位）:");
    scanf("%s", t->launch);
    printf("请输入交易单接收方公钥（7位）:");
    scanf("%s", t->receive);
    printf("请输入交易单交易数额（7位）:");
    scanf("%s", t->amount);
}

// 初始化队列
void InitQueue(ts_link_queue*& q) {
    q = (ts_link_queue*)malloc(sizeof(ts_link_queue));
    q->front = q->rear = (ts_node*)malloc(sizeof(ts_node));
    q->size = 0;
    q->front->next = NULL;
}

// 入队操作
Status EnQueue(ts_link_queue*& q, Transactionsheet e) {
    ts_node* s = (ts_node*)malloc(sizeof(ts_node));
    s->ts = e;
    q->size++;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
    return 1;
}

// 出队操作
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

// 获取队列中指定位置的元素
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
