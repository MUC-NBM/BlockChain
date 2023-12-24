#include <stdio.h>
#include <stdlib.h>
#include "tsQueue.h"
#include <string.h>


//初始化每一个交易单
void initTs(Transactionsheet* t,int i)
{
	printf("-----------第%d个交易单---------\n",i+1);
    printf("请输入交易单id（7位）:");
    scanf_s("%s", t->id,sizeof(t->id));
    printf("请输入交易单发起方公钥（7位）:");
    scanf_s("%s", t->launch,sizeof(t->launch));
    printf("请输入交易单接收方公钥（7位）:");
    scanf_s("%s", t->receive,sizeof(t->receive));
    printf("请输入交易单交易数额（7位）:");
    scanf_s("%s", t->amount,sizeof(t->amount));
    
}

void InitQueue(ts_link_queue *&q)
{
	q = (ts_link_queue*)malloc(sizeof(ts_link_queue));
	q->front = q->rear = (ts_node*)malloc(sizeof(ts_node));
	q->size = 0;
	q->front->next = NULL;
}
Status EnQueue(ts_link_queue *&q, Transactionsheet e)
{
	ts_node* s = (ts_node*)malloc(sizeof(ts_node));
	/*s->data = e;*/
	//memcpy(s->ts,e, SHA256_BLOCK_SIZE);
	s->ts = e;
	q->size++;
	s->next = NULL;
	q->rear->next = s;
	q->rear = s;
	return 1;
}
Status DeQueue(ts_link_queue *&q, Transactionsheet& e)
{
	if (q->front == q->rear)
		return 0;
	ts_node* p = q->front->next;
	e = p->ts;
	q->size--;
	q->front->next = p->next;
	if (q->rear == p)
	{
		q->rear = q->front;
		free(p);
	}
	return 1;
}
Status getItem(ts_link_queue* q, Transactionsheet& e,int pos)
{
	ts_node* r=q->front;
	while (pos>1)
	{
		r = r->next;
		pos--;
	}
	ts_node* p = r->next;
	e = p->ts;
	return 1;
}

