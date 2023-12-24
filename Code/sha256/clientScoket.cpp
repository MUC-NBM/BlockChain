#include"clientScoket.h"
bool recivedFromServer(BYTE *localhash)
{
	int controll = 0;
	printf("请输入任意非0的键以接收server端的值......\n");
	scanf_s("%d", &controll);
	//while (controll != 0)
	//{
		//初始化
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		//创建套接字
		SOCKET clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		//向服务器发送消息
		sockaddr_in sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));			//每个字节都用0填充
		sockAddr.sin_family = PF_INET;
		sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		sockAddr.sin_port = htons(8888);
		connect(clntSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

		//接收服务器消息
		char szBuffer[MAXBYTE] = { 0 };
		recv(clntSock, szBuffer, MAXBYTE, NULL);

		//输出接收到的数据
		const char* str = (char*)localhash;
		printf("服务端发来的数据:");
		for (int i = 0; i < 32; i++)
		{
			printf("%x", szBuffer[i]);
			if (str[i] == szBuffer[i])
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		printf("\n");
		//向服务端发送消息
		//const char* str = "hello server";
		//send(clntSock, str, strlen(str) + sizeof(char), NULL);

		//关闭套接字
		closesocket(clntSock);

		//终止dll
		WSACleanup();
	//	printf("请输入任意非0的键以接收server端的值......\n");
	//	scanf_s("%d", &controll);
	//}
		return true;
}
