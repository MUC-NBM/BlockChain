#ifndef BlockTest_H
#define BlockTest_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define BlockTest_BLOCK_SIZE 32            // BlockTest outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORDS;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[64];
	WORDS datalen;
	unsigned long long bitlen;
	WORDS state[8];
} BlockTest_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void blockTest_init(BlockTest_CTX* ctx);//��ʼ���ṹ�弰��ر���
void blockTest_update(BlockTest_CTX* ctx, const BYTE data[], size_t len);//����
void blockTest_final(BlockTest_CTX* ctx, BYTE hash[]);//��ֵ

#endif   // BlockTest_H