#include "stdio.h"
#include "stdlib.h"
#include "BlockTest.h"
#include "tsQueue.h"
#include "time.h"
#include <string.h>
#include "block.h"

// 将字符串 t 拼接到字符串 s 的末尾
void linkchar(char* s, char* t) {
    while (*s != '\0') {
        s++;
    }
    while (*t != '\0') {
        *s++ = *t++;
    }
    *s = '\0';
}

// 获取一个随机数
int getRandom() {
    return rand();
}

// 计算随机数的位数
int calRandomLen(int a) {
    int len = 0;
    while (a > 0) {
        len++;
        a = a / 10;
    }
    return len;
}

Status calculateWorkload(BYTE* hash, ts_link_queue* ts) {
    char tsSum[256]; // 假设交易单字符串长度不超过 256

    Transactionsheet e;
    int pos = 1;
    getItem(ts, e, pos); // 获取第一个订单
    linkchar(e.launch, e.receive);
    linkchar(e.launch, e.amount);
    strcpy(tsSum, e.launch); // 复制第一个交易单的内容到 tsSum

    pos++;
    while (pos < 5) { // 如果交易单不为空
        getItem(ts, e, pos); // 获取指定位置的订单
        pos++;
        linkchar(tsSum, e.launch);
        linkchar(tsSum, e.receive);
        linkchar(tsSum, e.amount);
    }

    int nums = 0;
    while (nums < 1000) {
        int randNum = getRandom();
        int randNumlen = calRandomLen(randNum);

        BYTE bs[150]; // 假设拼接数组大小不超过 150
        int len = randNumlen + BlockTest_BLOCK_SIZE + strlen(tsSum);

        // 拼接随机数、哈希值和交易单字符串到 bs 数组中
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

        // 计算哈希值
        BYTE buf[BlockTest_BLOCK_SIZE];
        BlockTest_CTX ctx;
        blockTest_init(&ctx);
        blockTest_update(&ctx, bs, len);
        blockTest_final(&ctx, buf);

        // 判断是否符合条件（前8位为0）
        if (buf[0] == 0) {
            return 1; // 工作量证明成功
        }
        nums++;
    }

    return 0; // 未找到满足条件的哈希值
}
