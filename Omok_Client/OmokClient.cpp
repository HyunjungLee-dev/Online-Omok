#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//#define BUF_SIZE 100
//#define NAME_SIZE 20
//
//unsigned WINAPI SendMsg(void* arg);
//unsigned WINAPI RecvMsg(void* arg);
void ErrorHandling(const char * msg);

//char name[NAME_SIZE] = "[DEFAULT]";
//char msg[BUF_SIZE];

int main()
{
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	//sprintf(name, "[%s]", argv[3]);
	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(9000);

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	//hSndThread =
	//	(HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	//hRcvThread =
	//	(HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	//WaitForSingleObject(SendMsg, INFINITE);
	//WaitForSingleObject(RecvMsg, INFINITE);
	closesocket(hSock);
	WSACleanup();
	return 0;
}

//unsigned WINAPI SendMsg(void* arg)
//{
//
//}
//
//unsigned WINAPI RecvMsg(void* arg)
//{
//
//}

void ErrorHandling(const char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}