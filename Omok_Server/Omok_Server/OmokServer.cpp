#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;

#define BUF_SIZE 100
#define MAX_CLNT 2

unsigned WINAPI HandleClnt(void* arg);
void SendMsg(char * msg, int len);
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

		if (clntCnt >= 2)
			continue;
	
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);

		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		printf("Connected client IP : %s \n", inet_ntoa(clntAdr.sin_addr));

		closesocket(hServSock);
		WSACleanup(); //���� ���̺귯�� ����
		return 0;
	}
}

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	// ���� �� ������ ����Ʈ �� (�� EOF ���� �� 0), ���� �� SOCKET_ERROR ��ȯ
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{

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

void SendMsg(char* msg, int len)
{
	int i;
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)
		send(clntSocks[i], msg, len, 0);
	ReleaseMutex(hMutex);
}

void ErrorHandling(const char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}