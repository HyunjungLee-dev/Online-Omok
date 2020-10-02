#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;

#define BUF_SIZE 100
#define MAX_CLNT 2

unsigned WINAPI HandleClnt(void* arg);
void SendMsg(char * msg, int len);
void ErrorHandling(char* msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE hThread;

	if (argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	//���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	//�ʱ�ȭ
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	//bind
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	//listen
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (true)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		if (clntCnt < MAX_CLNT)
		{
			WaitForSingleObject(hMutex, INFINITE);
			clntSocks[clntCnt++] = hClntSock;
			ReleaseMutex(hMutex);

			hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
			printf("Connected client IP : %s \n", inet_ntoa(clntAdr.sin_addr));
		}
		else
		{
			printf("Connection is not possible \n");
			closesocket(hClntSock);
		}
		closesocket(hServSock);
		WSACleanup(); //���� ���̺귯�� ����
		return 0;
	}
}

//���� �������� �����͸� ����(��Ŷ)
// ��[][], ���� ����, ����(2��)�� ����, �ش��� player msg, ���� ����
// ���� : ����, ��,��
//�������� ������ ���� Ȯ��

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	// ���� �� ������ ����Ʈ �� (�� EOF ���� �� 0), ���� �� SOCKET_ERROR ��ȯ
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		/*1. recv ����/���� 
		  2. �÷��� ��  ���� ���� �ʱ�ȭ
		  3. ������ ���°Ϳ� ���� Ȯ��
		  4. ���� �������� ������ ��� ������ �÷���
		  5. ���� ���� ����*/


	}


}

void ErrorHandling(const char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}