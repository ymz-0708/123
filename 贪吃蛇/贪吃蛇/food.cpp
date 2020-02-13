#include <time.h>
#include <stdlib.h>
#include "food.h"
#include "Game.h"

CFood::CFood(int x, int y, char pic) :CUnit(x, y, pic)
{
	//srand((unsigned int)time(NULL));
}

CFood::~CFood()
{
}

void CFood::createPos(vector<CUnit> *vec)
{
	while (true)
	{
		int x = CGame::KLEFT + 1 + rand() % (CGame::KWIDTH - 2);
		int y = CGame::KUP + 3 + rand() % (CGame::KHEIGHT - 2);
		size_t i = 0;
		for (i = 0; i < vec->size(); i++)
		{
			if (x == vec->at(i).m_iX && y == vec->at(i).m_iY)
			{
				//����ǰ�Ѿ����ɵ�λ����������
				break;
			}
		}//�������һ��ʳ��
		if (i == vec->size())
		{
			m_iX = x;
			m_iY = y;
			return;
		}
	}
}