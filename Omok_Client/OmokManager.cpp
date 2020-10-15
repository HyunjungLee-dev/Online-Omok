#include "OmokManager.h"



OmokManager::OmokManager()
{

}

void OmokManager::Init(PLAYER_COLOR color)
{
	m_Player.SetColor(color);

	if (color == PLAYER_BLACK)
	{
		m_Player.SetCursorIcon(BLACKTEAMICON);
		m_Player.SetStoneIcon(BLACKTEAMICON);
	}
	else if (color == PLAYER_WHITE)
	{
		m_Player.SetCursorIcon(WHITETEAMICON);
		m_Player.SetStoneIcon(WHITETEAMICON);
	}

	

}

void OmokManager::DrawMap()
{
	system("cls");
	m_MapDrawManager.printMap(WIDTH, HEIGHT);
	DrawCurPlayerInfo();
}

void OmokManager::DrawCurPlayerInfo()
{
	string str = "Player" + to_string(m_Player.GetColor());
	m_MapDrawManager.DrawMidText(str, WIDTH, HEIGHT + 2);
//	m_MapDrawManager.DrawMidText("Turn : " + to_string(m_iTurn) + "  ", m_iWidth, m_iHeight + 4);
}

void OmokManager::Playing()
{

}

void OmokManager::Input()
{
	char ch = getch();
	switch (ch)
	{
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_DOWN:
			break;
		case KEY_ESC:
			break;
		case KEY_DROP:
			break;
	}
}


OmokManager::~OmokManager()
{
}
