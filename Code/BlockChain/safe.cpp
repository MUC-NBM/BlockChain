#include "stdio.h"
#include "stdlib.h"
#include "BlockTest.h"
#include "block.h"


bool isSameHash(BYTE* hash1, BYTE* hash2)
{
	//printf("区块1：");
	//for (int i = 0; i < BlockTest_BLOCK_SIZE; i++)
	//{
	//	printf("%x", hash1[i]);
	//}
	//printf("\n");
	//printf("区块2：");
	//for (int i = 0; i < BlockTest_BLOCK_SIZE; i++)
	//{
	//	printf("%x", hash2[i]);
	//}
	//printf("\n");
	for (int i = 0; i < BlockTest_BLOCK_SIZE; i++)
	{
		if (hash1[i] != hash2[i])
			return false;
	}
	return true;
}
bool isSameBlock(BlockNode*& localBlock, BlockNode*& otherBlock)
{
	BlockNode* r = localBlock, * s = otherBlock;
	if (getLength(r) == getLength(s))//长度是否一样
	{
		//第一个节点判断
		if (!isSameHash(r->hash, s->hash))
			return false;
		//遍历后续，进行判断
		while (r->previous!=NULL&&s->previous!=NULL)
		{
			r = r->previous;
			s = s->previous;
			if (!isSameHash(r->hash, s->hash))
				return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool havePermission(BlockNode*& localBlock,BlockNode *&newBlcok,int flag)
{
	//编号判断作为提示信息
	int m, n;
	if (flag == 1)
	{
		m = 2, n = 3;
	}
	else if(flag==2)
	{
		m = 1, n = 3;
	}
	else
	{
		m = 1, n = 2;
	}
	printf("请输入选取其他任意客户端编号，进行获取其他客户端的数据：%d or %d：", m, n);
	//选择本客户端进行区块验证的其他客户端编号
	int rflag;
	scanf_s("%d", &rflag);
	//模拟区块进行验证的时候，客户端临时根据数据文件生成区块链
	BlockNode* otherlocalBlock;
	FILE* fpRead;
	if (rflag == 1)
	{
		fpRead = fopen("1.txt", "r");
	}
	else if (rflag == 2)
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
			InitBlockChain3(otherlocalBlock, fpRead);
			//printf("当前指针位置：%d\n", ftell(fpRead));
		}
		else if (num > 1)
		{
			BlockNode* otherlocalBlock2;
			InitBlockChain3(otherlocalBlock2, fpRead);
			//printf("当前指针位置：%d\n", ftell(fpRead));
			addBlockChain(otherlocalBlock, otherlocalBlock2);
		}
		else
		{
			break;
		}
		//printf("%c",getc(fpRead));
	}
	//printf("num=%d\n", num);
	fclose(fpRead);
	//printf("---------------------------当前区块链长度：%d----------------------------\n", getLength(otherlocalBlock));
	//showBlock(otherlocalBlock);
	bool mindflag = false;
	//对比区块链
	if (isSameBlock(localBlock, otherlocalBlock))
	{
		printf("区块链一样！\n");
		//通过其他客户端的交易信息生成对比hash，替代了用户手动输入
		BlockNode* otherNewBlock;
		FILE* fpRead;
		if (rflag == 1)
		{
			fpRead = fopen("new1.txt", "r");
		}
		else if (rflag == 2)
		{
			fpRead = fopen("new2.txt", "r");
		}
		else
		{
			fpRead = fopen("new3.txt", "r");
		}
		int num = 0;
		while (!feof(fpRead))
		{
			num++;
			if (num == 1)
			{
				InitBlockChain3(otherNewBlock, fpRead);
				//printf("当前指针位置：%d\n", ftell(fpRead));
			}
			else if (num > 1)
			{
				BlockNode* otherlocalBlock2;
				InitBlockChain3(otherlocalBlock2, fpRead);
				//printf("当前指针位置：%d\n", ftell(fpRead));
				addBlockChain(otherNewBlock, otherlocalBlock2);
			}
			else
			{
				break;
			}
			//printf("%c",getc(fpRead));
		}
		//printf("num=%d\n", num);
		fclose(fpRead);
		if (isSameHash(newBlcok->hash,otherNewBlock->hash ))
		{
			mindflag = true;
			printf("新区块一样！\n");
		}
		else {
			mindflag = false;
			printf("新区块不一样！\n");
		}
		
	}
	else
	{
		mindflag = false;
		printf("区块链不一样！\n");
	}
	
	return mindflag;

}

