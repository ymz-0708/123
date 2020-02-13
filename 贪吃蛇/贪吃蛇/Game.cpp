#include "Game.h"
#include "Tools.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

const int CGame::KLEFT = 5;
const int CGame::KUP = 2;
const int CGame::KWIDTH = 70;
const int CGame::KHEIGHT = 20;
const int CGame::KSCORE_OFFSET = 50;
const int CGame::KLEVEL_OFFSET = 65;

CGame::CGame()
{
	this->m_pFood = new CFood();
	this->m_pSnake = new CSnake();
	this->m_iScore = 0;
	this->m_iLevel = 1;

	drawGameArea();
	drawGameInfo();
}


CGame::~CGame()
{
	delete m_pFood;
	delete m_pSnake;
	m_pFood = NULL;
	m_pSnake = NULL;
}//��ֹҰָ��Ĵ���

/*
-------------------------
|                       |
|-----------------------|
|                       |
|                       |
|        ****           |
|                       |
|                       |
|                       |
-------------------------
*/
void CGame::drawGameArea()
{
	CTools::gotoxy(KLEFT, KUP);
	for (int j = 0; j < KWIDTH; j++)
	{
		cout << "-";
	}

	for (int i = 0; i < KHEIGHT; i++)
	{
		CTools::gotoxy(KLEFT, KUP + 1 + i);
		cout << "#";
		CTools::gotoxy(KLEFT + KWIDTH - 1, KUP + 1 + i);
		cout << "#";
	}

	CTools::gotoxy(KLEFT, KUP + KHEIGHT + 1);
	for (int k = 0; k < KWIDTH; k++)
	{
		cout << "-";
	}

	CTools::gotoxy(KLEFT + 1, KUP + 2);
	for (int i = 0; i < KWIDTH - 2; i++)
	{
		cout << "-";

	}
}

void CGame::drawGameInfo()
{
	CTools::gotoxy(KLEFT + 1, KUP + 1);
	cout << "��Ϸ���ƣ�̰����";
	CTools::gotoxy(KLEFT + 20, KUP + 1);
	cout << "��д�ߣ�������";
	CTools::gotoxy(KLEFT + 40, KUP + 1);
	cout << "��ǰ�÷�";
	CTools::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << m_iScore;
	CTools::gotoxy(KLEFT + 55, KUP + 1);
	cout << "��ǰ�ؿ�";
	CTools::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << m_iLevel;
}

void CGame::run()
{
	m_pFood->createPos(&(m_pSnake->m_vecBody));
	m_pFood->show();
	m_pSnake->showSnake();
	int key = 0;
	bool stopFlag = true;
	bool pauseFlag = false;
	while (key != VK_ESCAPE && stopFlag)  //0x1b
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == VK_SPACE)
			{
				pauseFlag = !pauseFlag;//�ո����ͣ
			}
			m_pSnake->changeDirection(key);
		}
		else
		{
			if (pauseFlag)
			{
				continue;
			}
			m_pSnake->move();
			if (m_pSnake->eatFood(m_pFood))
			{
				//�ӷ�   ������  �ı���Ϸ��Ϣ
				m_iScore += 10;
				if (checkLevel())
				{
					stopFlag = false;
				}
				changeInfo();
				m_pFood->createPos(&(m_pSnake->m_vecBody));
				m_pFood->show();
			}
			//����Ƿ�ײǽ
			//����Ƿ��Բ�
			if (checkFailed())
			{
				stopFlag = false;
				CTools::gotoxy(35, 10);
				cout << "GAME OVER";
			}
		}
	}
}

bool CGame::checkFailed()
{
	//����Ƿ�ײǽ
	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iX <= CGame::KLEFT)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iX >= CGame::KLEFT + CGame::KWIDTH - 1)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iY <= CGame::KUP + 2)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iY >= CGame::KUP + CGame::KHEIGHT + 1)
	{
		return true;
	}

	//����Ƿ��Բ�
	for (int i = 4; i < m_pSnake->m_iLength; i++)
	{
		if (m_pSnake->m_vecBody[0].m_iX == m_pSnake->m_vecBody[i].m_iX && m_pSnake->m_vecBody[0].m_iY == m_pSnake->m_vecBody[i].m_iY)
		{
			return true;
		}
	}

	return false;
}

bool CGame::checkLevel()
{
	int temp = m_iScore / 30 + 1;
	if (temp == m_iLevel)
	{
		return false;
	}
	m_iLevel = temp;
	switch (m_iLevel)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		//ͨ��
		CTools::gotoxy(35, 18);
		cout << "ţ��!!!!" << endl;
		return true;
		break;
	}
	return false;
}

void CGame::changeInfo()
{
	CTools::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << "  ";
	CTools::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << m_iScore;
	CTools::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << "  ";
	CTools::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << m_iLevel;
}