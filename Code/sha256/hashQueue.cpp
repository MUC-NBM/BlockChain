#include <stdio.h>
#include <stdlib.h>
#include "hashQueue.h"
#include <string.h>

//初始化每一个交易单

void InitQueueHash(hash_link_queue*& q)
{
	q = (hash_link_queue*)malloc(sizeof(hash_link_queue));
	q->front = q->rear = (hash_node*)malloc(sizeof(hash_node));
	q->size = 0;
	q->front->next = NULL;
}
Status EnQueueHash(hash_link_queue*& q, BYTE* e)
{
	hash_node* s = (hash_node*)malloc(sizeof(hash_node));
	
	memcpy(s->hashTs,e, SHA256_BLOCK_SIZE);
	q->size++;
	s->next = NULL;
	q->rear->next = s;
	q->rear = s;
	return 1;
}
Status DeQueueHash(hash_link_queue*& q, BYTE* e)
{
	if (q->front == q->rear)
		return 0;
	hash_node* p = q->front->next;
	memcpy(e,p->hashTs,SHA256_BLOCK_SIZE);
	q->size--;
	q->front->next = p->next;
	if (q->rear == p)
	{
		q->rear = q->front;
		free(p);
	}
	return 1;
}
