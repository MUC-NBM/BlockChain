#ifndef BLOCK_H
#define BLOCK_H

#include "sha256.h"
#include "hashQueue.h"
#include "tsQueue.h"
//����
typedef struct ts_link_queue;
typedef struct node
{
    /*��һ������Ĺ�ϣ,��������ʱ����ֵΪ��*/
    BYTE priorHash[SHA256_BLOCK_SIZE];
    /*������Ĺ�ϣ */
    BYTE hash[SHA256_BLOCK_SIZE];
    /*ָ����һ�������ָ�� */
    struct node* previous;
    /*���������������ж����Ĺ�ϣ������֮���������й�ϣ��������*/
    hash_link_queue *hashSum;
    /*���׵����У����������׵�*/
    ts_link_queue *ts;
} BlockNode;
void showBlock(BlockNode*& b);//��ʾ��ǰ������ÿ�������hash

void InitBlockChain(BlockNode*& oneBlock, ts_link_queue* q);//�Խ��׵����еķ�ʽ��ʼ��
void InitBlockChain3(BlockNode*& oneBlock, FILE* fpRead);//�Զ�ȡ�ļ��ķ�ʽ��ʼ��

void getPreviousHash(BlockNode*& orginalBlock, BYTE* oneHash);//�õ���һ����hash
void addBlockChain(BlockNode*& orginalBlock, BlockNode*& newBlock);//����

int getLength(BlockNode*& b);//��������������
void getTs(BlockNode* b);//ͨ���û������ʼ�����齻�׵�
void getTsBydir(BlockNode* b, ts_link_queue* q);//ͨ�����׵����г�ʼ���µ����齻�׵�
void getHash(BlockNode* b);//���������е�ÿһ�����׵���ϣ
void calHash(BlockNode* b);//��������Hash

void writeNewBlock(BlockNode* b, int flag);//������ʱ����������Ϣ

void writeToLocalFile(BlockNode* b,int flag);//����������д�뵽��������
#endif   
