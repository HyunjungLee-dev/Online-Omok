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

	//윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	//초기화
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
		WSACleanup(); //윈속 라이브러리 해제
		return 0;
	}
}

//게임 전반적인 데이터를 관리(패킷)
// 돌[][], 돌의 색깔, 유저(2명)의 정보, 해당턴 player msg, 게임 상태
// 유저 : 돌색, 승,패
//오목판의 오목의 여부 확인

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	// 성공 시 수신한 바이트 수 (단 EOF 전송 시 0), 실패 시 SOCKET_ERROR 반환
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		/*1. recv 에러/종료 
		  2. 플레이 돌  색에 따른 초기화
		  3. 유저가 들어온것에 대한 확인
		  4. 돌을 놓음으로 한쪽은 대기 한쪽은 플레이
		  5. 오목 승패 판정*/


	}


}

void ErrorHandling(const char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}