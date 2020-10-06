#include "MapDraw.h"



MapDraw::MapDraw()
{
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


MapDraw::~MapDraw()
{
}
