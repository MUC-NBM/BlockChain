#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "BlockTest.h"
#include "block.h"
#include "workProof.h"
#include "tsQueue.h"
#include "safe.h"
int main()
{

	////������������
	printf("�˴�ģ�������ͻ��ˣ�������ͻ��˱�ţ�(1 or 2 or 3)��");
	int flag = 0;
	scanf_s("%d", &flag);
	printf("---------------���ڶ�ȡ�����ļ�����ʼ����������ing.......-------------\n");
	BlockNode* b1;
	FILE* fpRead;//��ȡ�������ݣ�������������ʼ��
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
			//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
		}
		else if (num>1)
		{
			BlockNode* b2;
			InitBlockChain3(b2, fpRead);
			//printf("��ǰָ��λ�ã�%d\n", ftell(fpRead));
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
	printf("---------------��ʼ������������ɣ�-------------\n");
	//δ�����κ�������½��׵�
	while (true)
	{
		printf("---------------------------��ǰ���������ȣ�%d----------------------------\n", getLength(b1));
		showBlock(b1);
		printf("-----------------------------�����齨��-----------------------------------\n", getLength(b1));
		printf("--------------------------�������µĽ��׵�-------------------------------\n");
		//��δ���뵽�κ�����Ľ��׵�����
		ts_link_queue* q;
		InitQueue(q);
		BYTE testHash[BlockTest_BLOCK_SIZE];
		for (int i = 0; i < 4; i++)
		{
			Transactionsheet e;
			initTs(&e,i);
			EnQueue(q, e);
		}

		//������֤������
		//��ȡ��һ����hash
		getPreviousHash(b1, testHash);

		//������
		BlockNode* b2;
		InitBlockChain(b2, q);
		//��ʱ����������Ϣд���ļ��У����������ͻ��˶�ȡ���ͻ�����������Ϣ
		writeNewBlock(b2,flag);	
		if (calculateWorkload(testHash,b2->ts))
		{
			printf("������֤���ɹ���ֱ������!\n");
			addBlockChain(b1, b2);
			int pass;
			printf("�ȴ������ͻ���ͶƱ��Ϊ���ü����ͻ���ͬ����...��������ֵ����������д�뱾�أ�");
			scanf_s("%d", &pass);
			printf("��������Ϣд�뱾��.......\n");
			writeToLocalFile(b1,flag);
		}
		else
		{
			printf("������֤��ʧ�ܣ�������������жԱ���֤\n");
			//printf("����������֮ǰ��%d\n", getLength(b1));
			
			if (havePermission(b1,b2,flag))
			{
				printf("����������뱾����������\n");
				addBlockChain(b1, b2);
				int pass;
				printf("�ȴ������ͻ���ͶƱ��Ϊ���ü����ͻ���ͬ����...��������ֵ����������д�뱾�أ�");
				scanf_s("%d", &pass);
				printf("��������Ϣд�뱾��.......\n");
				writeToLocalFile(b1, flag);
			}
			else 
			{
				printf("����������ٵģ���׼����!\n");
			}
		}

	}

	return(0);
}


