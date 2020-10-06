#pragma once
#include "Mecro.h"
class MapDraw
{
public:
	MapDraw();
	~MapDraw();

	void printMap(int Width, int Height);
	
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

