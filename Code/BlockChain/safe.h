#pragma once
#ifndef SAFE_H
#define SAFE_H

#include "BlockTest.h"
bool isSameHash(BYTE* hash1, BYTE* hash2);//对比hash
bool havePermission(BlockNode*& localBlock, BlockNode*& newBlcok, int flag);//对比区块

#endif
