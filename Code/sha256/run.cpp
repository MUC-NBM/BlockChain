#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"
#include "block.h"
#include "workProof.h"
#include "tsQueue.h"
#include "safe.h"
int main()
{

	////创建本地区块
	printf("此处模拟三个客户端，请输入客户端编号：(1 or 2 or 3)：");
	int flag = 0;
	scanf_s("%d", &flag);
	printf("---------------正在读取本地文件，初始化本地区块ing.......-------------\n");
	BlockNode* b1;
	FILE* fpRead;//读取本地数据，进行区块链初始化
	if (flag == 1)
	{
		fpRead = fopen("1.txt", "r");
	}
	else if (flag == 2)
	{
		fpRead = fopen("2.txt", "r");
	}
	else
	{
		fpRead = fopen("3.txt", "r");
	}

	int num = 0;
	while (!feof(fpRead))
	{
		num++;
		if (num == 1)
		{
			InitBlockChain3(b1, fpRead);
			//printf("当前指针位置：%d\n", ftell(fpRead));
		}
		else if (num>1)
		{
			BlockNode* b2;
			InitBlockChain3(b2, fpRead);
			//printf("当前指针位置：%d\n", ftell(fpRead));
			addBlockChain(b1, b2);
		}
		else
		{
			break;
		}
		//printf("%c",getc(fpRead));
	}
	//printf("num=%d\n", num);
	fclose(fpRead);
	printf("---------------初始化本地区块完成！-------------\n");
	//未加入任何区块的新交易单
	while (true)
	{
		printf("---------------------------当前区块链长度：%d----------------------------\n", getLength(b1));
		showBlock(b1);
		printf("-----------------------------新区块建立-----------------------------------\n", getLength(b1));
		printf("--------------------------请输入新的交易单-------------------------------\n");
		//尚未加入到任何区块的交易单队列
		ts_link_queue* q;
		InitQueue(q);
		BYTE testHash[SHA256_BLOCK_SIZE];
		for (int i = 0; i < 4; i++)
		{
			Transactionsheet e;
			initTs(&e,i);
			EnQueue(q, e);
		}

		//工作量证明计算
		//获取上一区块hash
		getPreviousHash(b1, testHash);

		//新区块
		BlockNode* b2;
		InitBlockChain(b2, q);
		//暂时把新区块信息写入文件中，用于其他客户端读取本客户端新区块信息
		writeNewBlock(b2,flag);	
		if (calculateWorkload(testHash,b2->ts))
		{
			printf("工作量证明成功！直接上链!\n");
			addBlockChain(b1, b2);
			int pass;
			printf("等待其他客户端投票（为了让几个客户端同步）...输入任意值，将新数据写入本地：");
			scanf_s("%d", &pass);
			printf("新区块信息写入本地.......\n");
			writeToLocalFile(b1,flag);
		}
		else
		{
			printf("工作量证明失败！与其他区块进行对比验证\n");
			//printf("加入新区块之前：%d\n", getLength(b1));
			
			if (havePermission(b1,b2,flag))
			{
				printf("将新区块加入本地区块链！\n");
				addBlockChain(b1, b2);
				int pass;
				printf("等待其他客户端投票（为了让几个客户端同步）...输入任意值，将新数据写入本地：");
				scanf_s("%d", &pass);
				printf("新区块信息写入本地.......\n");
				writeToLocalFile(b1, flag);
			}
			else 
			{
				printf("新区块是虚假的，不准加入!\n");
			}
		}

	}

	return(0);
}


