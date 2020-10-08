#include "OmokManager.h"



OmokManager::OmokManager()
{
}

void OmokManager::InitMap()
{

}


void OmokManager::DrawMap()
{
	system("cls");
	m_MapDrawManager.printMap(WIDTH, HEIGHT);
}

void OmokManager::DrawCurPlayerInfo()
{
	printf("Player Name :");
	printf("Turn : ");
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
