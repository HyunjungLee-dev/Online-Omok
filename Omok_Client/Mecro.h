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

