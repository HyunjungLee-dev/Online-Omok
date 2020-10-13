#pragma once
#include "Player.h"

#define BLACKTEAMICON "¡Û"
#define WHITETEAMICON "¡Ü"

class OmokManager
{
private:
	MapDraw m_MapDrawManager;
	Player m_Player;
public:
	OmokManager();
	~OmokManager();

	void Init(PLAYER_COLOR color);
	void DrawMap();
	void Playing();
	void DrawCurPlayerInfo();
	void Input();

};

