#include <windows.h>
#include <iostream>
#include <process.h>
#include "Mecro.h"
using namespace std;

#define BUF_SIZE 1024
#define MAX_CLNT 2 // ��, ��
 
unsigned WINAPI HandleClnt(void* arg);
void SendMsg(char * msg);
void ErrorHandling(const char* msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

int main()
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE hThread;


	//���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	//�ʱ�ȭ
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(9000);

	//bind
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	//listen
	if (listen(hServSock, 2) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (true)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		if (clntCnt >= MAX_CLNT)
		{
			printf("���� ���� Ŭ���̾�Ʈ �� �ʰ�\n");
			continue;
		}

		//������ Ŭ���̾�Ʈ ������ �迭��
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);

		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		printf("Connected client IP : %s \n", inet_ntoa(clntAdr.sin_addr));
	}
		closesocket(hServSock);
		WSACleanup(); //���� ���̺귯�� ����
		return 0;
	
}

//��,�����,��

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	OmokData* pRequest;
	OmokData pResponse;
	PLAYER_COLOR color;
	// Ŭ���̾�Ʈ�� ������ request(��û) �޼����� ������ 
	// ������ response(����) �޼����� ������

	
	//���� �ι�° ���� char*
	// ���� �� ������ ����Ʈ �� (�� EOF ���� �� 0), ���� �� SOCKET_ERROR ��ȯ
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		if (strLen == SOCKET_ERROR)
		{
			printf("Ŭ���̾�Ʈ������ ������ ���� ����\n");
			//exit(0);
		}
		else if (strLen == 0)
		{
			printf("Ŭ���̾�Ʈ ������ ���� �Ǿ����ϴ�.\n");
			//exit(0);
		}

		//Ŭ���̾�Ʈ���� ���� �޼����� Ȯ���ϰ� �޼����� ������.
		pRequest = (OmokData*)msg;
		switch (pRequest->DataActionType)
		{
		case AT_COLOR_SET:
			if (hClntSock == clntSocks[PLAYER_BLACK])
			{
				color = PLAYER_BLACK;	
			}
			else if(hClntSock == clntSocks[PLAYER_WHITE])
			{
				color = PLAYER_WHITE;
			}
			pResponse.DataActionType = AT_COLOR_SET;
			pResponse.MainData = &color;
			send(hClntSock, (char*)&pResponse, sizeof(pResponse), 0);
			break;
		}

	}

	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++) //remove disconnected client
	{
		if (hClntSock == clntSocks[i])
		{
			while (i++ < clntCnt - 1)
				clntSocks[i] = clntSocks[i + i];
			break;
		}
	}
	clntCnt--;
	ReleaseMutex(hMutex);
	closesocket(hClntSock);
	return 0;
}

void SendMsg(char* msg)
{
	int i;
	WaitForSingleObject(hMutex, INFINITE);



	ReleaseMutex(hMutex);
}

void ErrorHandling(const char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}