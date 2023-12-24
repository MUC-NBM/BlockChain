#include "stdio.h"
#include "stdlib.h"
#include "sha256.h"
#include "block.h"


bool isSameHash(BYTE* hash1, BYTE* hash2)
{
	//printf("����1��");
	//for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
	//{
	//	printf("%x", hash1[i]);
	//}
	//printf("\n");
	//printf("����2��");
	//for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
	//{
	//	printf("%x", hash2[i]);
	//}
	//printf("\n");
	for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
	{
		if (hash1[i] != hash2[i])
			return false;
	}
	return true;
}
bool isSameBlock(BlockNode*& localBlock, BlockNode*& otherBlock)
{
	BlockNode* r = localBlock, * s = otherBlock;
	if (getLength(r) == getLength(s))//�����Ƿ�һ��
	{
		//��һ���ڵ��ж�
		if (!isSameHash(r->hash, s->hash))
			return false;
		//���������������ж�
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
	//����ж���Ϊ��ʾ��Ϣ
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
	printf("������ѡȡ��������ͻ��˱�ţ����л�ȡ�����ͻ��˵����ݣ�%d or %d��", m, n);
	//ѡ�񱾿ͻ��˽���������֤�������ͻ��˱��
	int rflag;
	scanf_s("%d", &rflag);
	//ģ�����������֤��ʱ�򣬿ͻ�����ʱ���������ļ�����������
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
			//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
		}
		else if (num > 1)
		{
			BlockNode* otherlocalBlock2;
			InitBlockChain3(otherlocalBlock2, fpRead);
			//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
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
	//printf("---------------------------��ǰ���������ȣ�%d----------------------------\n", getLength(otherlocalBlock));
	//showBlock(otherlocalBlock);
	bool mindflag = false;
	//�Ա�������
	if (isSameBlock(localBlock, otherlocalBlock))
	{
		printf("������һ����\n");
		//ͨ�������ͻ��˵Ľ�����Ϣ���ɶԱ�hash��������û��ֶ�����
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
				//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
			}
			else if (num > 1)
			{
				BlockNode* otherlocalBlock2;
				InitBlockChain3(otherlocalBlock2, fpRead);
				//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
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
			printf("������һ����\n");
		}
		else {
			mindflag = false;
			printf("�����鲻һ����\n");
		}
		
	}
	else
	{
		mindflag = false;
		printf("��������һ����\n");
	}
	
	return mindflag;

}

