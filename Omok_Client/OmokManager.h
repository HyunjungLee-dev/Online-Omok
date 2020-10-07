#pragma once
#include "MapDraw.h"
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
	void DrawInfoText();

};

