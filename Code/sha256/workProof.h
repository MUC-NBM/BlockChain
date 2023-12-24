#ifndef WORKPROOF_H
#define WORKPROOF_H

Status calculateWorkload( BYTE* hash, ts_link_queue* ts);//工作量证明
void linkchar(char* s, char* t);//char数组拼接
int getRandom();//随机数
int calRandomLen(int a);//计算随机数长度

#endif