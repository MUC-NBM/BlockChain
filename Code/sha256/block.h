#ifndef BLOCK_H
#define BLOCK_H

#include "sha256.h"
#include "hashQueue.h"
#include "tsQueue.h"
//区块
typedef struct ts_link_queue;
typedef struct node
{
    /*上一个区块的哈希,单个区块时，此值为空*/
    BYTE priorHash[SHA256_BLOCK_SIZE];
    /*本区块的哈希 */
    BYTE hash[SHA256_BLOCK_SIZE];
    /*指向上一个区块的指针 */
    struct node* previous;
    /*保存区块链中所有订单的哈希，并且之后会用其进行哈希迭代计算*/
    hash_link_queue *hashSum;
    /*交易单队列，保存多个交易单*/
    ts_link_queue *ts;
} BlockNode;
void showBlock(BlockNode*& b);//显示当前区块链每个区块的hash

void InitBlockChain(BlockNode*& oneBlock, ts_link_queue* q);//以交易单队列的方式初始化
void InitBlockChain3(BlockNode*& oneBlock, FILE* fpRead);//以读取文件的方式初始化

void getPreviousHash(BlockNode*& orginalBlock, BYTE* oneHash);//得到上一区块hash
void addBlockChain(BlockNode*& orginalBlock, BlockNode*& newBlock);//上链

int getLength(BlockNode*& b);//计算区块链长度
void getTs(BlockNode* b);//通过用户输入初始化区块交易单
void getTsBydir(BlockNode* b, ts_link_queue* q);//通过交易单队列初始化新的区块交易单
void getHash(BlockNode* b);//计算区块中的每一个交易单哈希
void calHash(BlockNode* b);//计算区块Hash

void writeNewBlock(BlockNode* b, int flag);//保存临时的新区块信息

void writeToLocalFile(BlockNode* b,int flag);//将区块数据写入到本地区块
#endif   
