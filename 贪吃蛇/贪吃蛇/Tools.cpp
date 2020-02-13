#include "Tools.h"
#include <Windows.h>

CTools::CTools()
{
}


CTools::~CTools()
{
}


void CTools::gotoxy(int x, int y)
{
	COORD coor;
	coor.X = x;
	coor.Y = y;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coor);
}
