#pragma once
#ifndef SAFE_H
#define SAFE_H

#include "sha256.h"
bool isSameHash(BYTE* hash1, BYTE* hash2);//�Ա�hash
bool havePermission(BlockNode*& localBlock, BlockNode*& newBlcok, int flag);//�Ա�����

#endif
