#include <windows.h>
#include <iostream>
#include <process.h>
#include "Mecro.h"
using namespace std;

#define BUF_SIZE 1024
#define MAX_CLNT 2 // 흑, 백
 
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


	//윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	//초기화
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
			printf("연결 가능 클라이언트 수 초과\n");
			continue;
		}

		//생성된 클라이언트 소켓을 배열에
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);

		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		printf("Connected client IP : %s \n", inet_ntoa(clntAdr.sin_addr));
	}
		closesocket(hServSock);
		WSACleanup(); //윈속 라이브러리 해제
		return 0;
	
}

//턴,컴페어,윈

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	OmokData* pRequest;
	OmokData pResponse;
	PLAYER_COLOR color;
	// 클라이언트는 서버에 request(요청) 메세지를 보내고 
	// 서버는 response(응답) 메세지를 보낸다

	
	//원형 두번째 인자 char*
	// 성공 시 수신한 바이트 수 (단 EOF 전송 시 0), 실패 시 SOCKET_ERROR 반환
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		if (strLen == SOCKET_ERROR)
		{
			printf("클라이언트에서의 데이터 수신 실패\n");
			//exit(0);
		}
		else if (strLen == 0)
		{
			printf("클라이언트 연결이 종료 되었습니다.\n");
			//exit(0);
		}

		//클라이언트에서 받은 메세지를 확인하고 메세지를 보낸다.
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