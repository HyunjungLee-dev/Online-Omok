#include "MapDraw.h"



MapDraw::MapDraw()
{
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}


void MapDraw::printMap(int Width, int Height)
{
   for (int y = 0; y < Height; y++)
   {
			for (int x = 0; x < Width; x++)
			{
				if (x == 0 && y == 0)
					cout << "¦£";
				else if (y == 0 && x == Width - 1)
					cout << "¦¤";
				else if (y == 0 && x > 0 && x < Width - 1)
					cout << "¦¨";
				else if (y == Height - 1 && x > 0 && x < Width - 1)
					cout << "¦ª";
				else if (x == 0 && y > 0 && y < Height - 1)
					cout << "¦§";
				else if (x == Width - 1 && y > 0 && y < Height - 1)
					cout << "¦©";
				else if (x == 0 && y == Height - 1)
					cout << "¦¦";
				else if (x == Width - 1 && y == Height - 1)
					cout << "¦¥";
				else
					cout << "¦«";
			}
			cout << endl;
   }
	return;
}

void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}


MapDraw::~MapDraw()
{
}
