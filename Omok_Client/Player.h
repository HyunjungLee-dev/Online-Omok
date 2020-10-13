#pragma once
#include"MapDraw.h"

struct Point
{
	int m_ix;
	int m_iy;
};

class Player
{
private:
	MapDraw m_DrawManager;
	Point* m_pStoneList;
	Point m_Cursor;
	int m_iStoneCount;
	PLAYER_COLOR m_eColor;
	string m_strCursorIcon;
	string m_strStoneIcon;
public:
	void AllStoneDraw();
	void DrawStone(int x, int y);
	bool CompareStone(int x, int y);
	void Move(char ch, int Width, int Height);
	//void DrawCursor();
	//void EraseCursor(int Width, int Height);
	//void PlayerSet(int Width, int Height);
	//void DeleteStone();

	inline int GetColor() { return (int)m_eColor; }
	inline void SetColor(PLAYER_COLOR color) { m_eColor = color; }
	inline void SetStoneIcon(string Icon) { m_strStoneIcon = Icon; }
	inline void SetCursorIcon(string Icon) { m_strCursorIcon = Icon; }

	Player();
	~Player();
};

