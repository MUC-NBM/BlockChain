#include"clientScoket.h"
bool recivedFromServer(BYTE *localhash)
{
	int controll = 0;
	printf("�����������0�ļ��Խ���server�˵�ֵ......\n");
	scanf_s("%d", &controll);
	//while (controll != 0)
	//{
		//��ʼ��
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		//�����׽���
		SOCKET clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		//�������������Ϣ
		sockaddr_in sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));			//ÿ���ֽڶ���0���
		sockAddr.sin_family = PF_INET;
		sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		sockAddr.sin_port = htons(8888);
		connect(clntSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

		//���շ�������Ϣ
		char szBuffer[MAXBYTE] = { 0 };
		recv(clntSock, szBuffer, MAXBYTE, NULL);

		//������յ�������
		const char* str = (char*)localhash;
		printf("����˷���������:");
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
		//�����˷�����Ϣ
		//const char* str = "hello server";
		//send(clntSock, str, strlen(str) + sizeof(char), NULL);

		//�ر��׽���
		closesocket(clntSock);

		//��ֹdll
		WSACleanup();
	//	printf("�����������0�ļ��Խ���server�˵�ֵ......\n");
	//	scanf_s("%d", &controll);
	//}
		return true;
}
