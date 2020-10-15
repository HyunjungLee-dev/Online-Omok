#include "OmokManager.h"

#define BUF_SIZE 1024
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void * arg);
unsigned WINAPI RecvMsg(void * arg);
void ErrorHandling(const char * msg);

//전달만 차이 나머지는 그대로

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];
OmokManager g_OmokManager;
//User_Cursor g_Player;
GameInfo g_Gameinfo;

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

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(9000);

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error");
	}

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);
	closesocket(hSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI SendMsg(void * arg)   // send thread main
{
	SOCKET hSock = *((SOCKET*)arg);
	OmokData m_Request;
	char nameMsg[NAME_SIZE + BUF_SIZE];

	//지금 오목 플레이어 셋, 오목 전체 셋

	while (true)
	{

		cin >> msg;

		switch (g_Gameinfo.ActionType)
		{
		case AT_COLOR_SET:
			m_Request.DataActionType = AT_COLOR_SET;
			m_Request.MainData = NULL;
			send(hSock, (char*)&m_Request, sizeof(m_Request),0);
			break;
		case AT_WAIT:
			m_Request.DataActionType = AT_WAIT;
			m_Request.MainData = NULL;
			send(hSock, (char*)&m_Request, sizeof(m_Request), 0);
			break;
		}

		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			exit(0);
		}

		sprintf(nameMsg, "%s %s", name, msg);
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}

	return 0;
}

unsigned WINAPI RecvMsg(void * arg)   // read thread main
{
	int hSock = *((SOCKET*)arg);
	char msg[BUF_SIZE];
	int Size;
	OmokData* pResponse;
	PLAYER_COLOR* m_pColor;

	while (1)
	{

		g_OmokManager.DrawMap();

		Size = recv(hSock, msg, BUF_SIZE - 1, 0);

		if (Size == -1)
			return -1;

		pResponse = (OmokData*)msg;

		switch (pResponse->DataActionType)
		{
		case AT_COLOR_SET:
			m_pColor = (PLAYER_COLOR*)pResponse->MainData;
			g_OmokManager.Init(*m_pColor);
			g_Gameinfo.ActionType = AT_WAIT;
			break;
		}

	}

	return 0;
}


void ErrorHandling(const char *msg)
{
	cout << msg << "\n";
	exit(1);
}


