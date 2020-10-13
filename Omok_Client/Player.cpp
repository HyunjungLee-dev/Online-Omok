#include "Player.h"



Player::Player()
{
	m_pStoneList = NULL;
	m_iStoneCount = 0;
}

void Player::AllStoneDraw()
{
	for (int i = 0; i < m_iStoneCount; i++)
		m_DrawManager.DrawPoint(m_strStoneIcon, m_pStoneList[i].m_ix, m_pStoneList[i].m_iy);
}

void Player::DrawStone(int x, int y)
{
	if (CompareStone(x, y))
		m_DrawManager.DrawPoint(m_strStoneIcon, x, y);
}

bool Player::CompareStone(int x, int y)
{
	for (int i = 0; i < m_iStoneCount; i++)
	{
		if (m_pStoneList[i].m_ix == x && m_pStoneList[i].m_iy == y)
			return true;
	}
	return false;
}

void Player::Move(char ch, int Width, int Height)
{
	switch (ch)
	{
	case KEY_LEFT:
		if (m_Cursor.m_ix - 1 >= 0)
			m_Cursor.m_ix--;
		break;
	case KEY_RIGHT:
		if (m_Cursor.m_ix + 1 < Width)
			m_Cursor.m_ix++;
		break;
	case KEY_UP:
		if (m_Cursor.m_iy - 1 >= 0)
			m_Cursor.m_iy--;
		break;
	case KEY_DOWN:
		if (m_Cursor.m_iy + 1 < Height)
			m_Cursor.m_iy++;
		break;
	}
}

Player::~Player()
{
}
