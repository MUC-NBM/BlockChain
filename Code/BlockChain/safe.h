#pragma once
#ifndef SAFE_H
#define SAFE_H

#include "BlockTest.h"
bool isSameHash(BYTE* hash1, BYTE* hash2);//�Ա�hash
bool havePermission(BlockNode*& localBlock, BlockNode*& newBlcok, int flag);//�Ա�����

#endif
