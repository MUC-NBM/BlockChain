#include "stdio.h"
#include "stdlib.h"
#include "BlockTest.h"
#include "tsQueue.h"
#include "time.h"
#include <string.h>
#include "block.h"

// ���ַ��� t ƴ�ӵ��ַ��� s ��ĩβ
void linkchar(char* s, char* t) {
    while (*s != '\0') {
        s++;
    }
    while (*t != '\0') {
        *s++ = *t++;
    }
    *s = '\0';
}

// ��ȡһ�������
int getRandom() {
    return rand();
}

// �����������λ��
int calRandomLen(int a) {
    int len = 0;
    while (a > 0) {
        len++;
        a = a / 10;
    }
    return len;
}

Status calculateWorkload(BYTE* hash, ts_link_queue* ts) {
    char tsSum[256]; // ���轻�׵��ַ������Ȳ����� 256

    Transactionsheet e;
    int pos = 1;
    getItem(ts, e, pos); // ��ȡ��һ������
    linkchar(e.launch, e.receive);
    linkchar(e.launch, e.amount);
    strcpy(tsSum, e.launch); // ���Ƶ�һ�����׵������ݵ� tsSum

    pos++;
    while (pos < 5) { // ������׵���Ϊ��
        getItem(ts, e, pos); // ��ȡָ��λ�õĶ���
        pos++;
        linkchar(tsSum, e.launch);
        linkchar(tsSum, e.receive);
        linkchar(tsSum, e.amount);
    }

    int nums = 0;
    while (nums < 1000) {
        int randNum = getRandom();
        int randNumlen = calRandomLen(randNum);

        BYTE bs[150]; // ����ƴ�������С������ 150
        int len = randNumlen + BlockTest_BLOCK_SIZE + strlen(tsSum);

        // ƴ�����������ϣֵ�ͽ��׵��ַ����� bs ������
        for (int i = 0, j = 0, k = 0; i < len; i++) {
            if (i < randNumlen) {
                bs[randNumlen - i - 1] = randNum % 10;
                randNum = randNum / 10;
            }
            if (i < randNumlen + BlockTest_BLOCK_SIZE && i >= randNumlen) {
                bs[i] = hash[j];
                j++;
            }
            if (i >= randNumlen + BlockTest_BLOCK_SIZE) {
                bs[i] = (BYTE)tsSum[k];
                k++;
            }
        }

        // �����ϣֵ
        BYTE buf[BlockTest_BLOCK_SIZE];
        BlockTest_CTX ctx;
        blockTest_init(&ctx);
        blockTest_update(&ctx, bs, len);
        blockTest_final(&ctx, buf);

        // �ж��Ƿ����������ǰ8λΪ0��
        if (buf[0] == 0) {
            return 1; // ������֤���ɹ�
        }
        nums++;
    }

    return 0; // δ�ҵ����������Ĺ�ϣֵ
}
