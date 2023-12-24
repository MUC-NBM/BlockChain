#pragma once
#ifndef CLIENTSCOKET_H
#define CLIENTSCOKET_H
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")		//º”‘ÿws2_32.dll
bool recivedFromServer(BYTE* localhash);

#endif