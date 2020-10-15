#pragma once
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <string>
using namespace std;

enum KEY
{
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_ESC = 27,
	KEY_DROP = 13,	//Enter
};

enum GAMESTATE
{
	WAITING,
	START,
	END
};

enum OMOK_BOARD_SIZE
{
	WIDTH = 20,
	HEIGHT = 20
};


enum PLAYER_COLOR
{
	NONE_COLOR=-1,
	PLAYER_BLACK,
	PLAYER_WHITE
};

//struct User_Cursor
//{
//	int x;
//	int y;
//	PLAYER_COLOR Pcolor = NONE_COLOR;
//};

enum ACTION_TYPE
{
	AT_COLOR_SET,
	AT_WAIT
};

struct OmokData
{
	void* MainData;
	ACTION_TYPE DataActionType;
};

struct GameInfo
{
	ACTION_TYPE		ActionType = AT_COLOR_SET;
	GAMESTATE	GameState = WAITING;
};