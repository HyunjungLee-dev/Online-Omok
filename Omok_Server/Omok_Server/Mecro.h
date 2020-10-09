#pragma once

enum PLAYER_COLOR
{
	PLAYER_BLACK,
	PLAYER_WHITE
};

struct Cursor
{
	int x;
	int y;
	PLAYER_COLOR Pcolor;
};

struct OmokData
{
	void* MainData;
	ACTION_TYPE DataActionType;
};

enum ACTION_TYPE
{
	AT_COLOR_SET
};