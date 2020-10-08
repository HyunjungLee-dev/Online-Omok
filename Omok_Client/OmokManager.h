#pragma once
#include "MapDraw.h"

struct GAMEINFO
{
	int	PlayerNum = -1;
	int	NowPlayer = 0;
	int WinPlayer = -1;
	GAMESTATE GameState = WAITING ;
};

class OmokManager
{
private:
	MapDraw m_MapDrawManager;
public:
	OmokManager();
	~OmokManager();

	void InitMap();
	void DrawMap();
	void Playing();
	void DrawCurPlayerInfo();
	void Input();

};

