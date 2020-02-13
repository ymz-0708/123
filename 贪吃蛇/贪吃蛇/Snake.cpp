#include "Snake.h"
#include <windows.h>



CSnake::CSnake(int x, int y, int length, Directions direction, int speed, char pic)
//x.y����ͷ���꣬length�ǳ��ȣ�direction�Ƿ���speed���ٶȣ�pic���ߵ�ͼ��
{
	m_iHeadX = x;
	m_iHeadY = y;
	m_iLength = length;
	m_enumCurrentDirection = direction;
	m_iSpeed = speed;
	m_cPic = pic;

	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < m_iLength; i++)
	{
		switch (m_enumCurrentDirection)
		{
		case UP://UP
			tempX = m_iHeadX;
			tempY = m_iHeadY + i;
			break;
		case DOWN://DOWN
			tempX = m_iHeadX;
			tempY = m_iHeadY - i;
			break;
		case LEFT://LEFT
			tempX = m_iHeadX + i;
			tempY = m_iHeadY;
			break;
		case RIGHT://RIGHT
			tempX = m_iHeadX - i;
			tempY = m_iHeadY;
			break;
		}
		CUnit unit(tempX, tempY, pic);
		m_vecBody.push_back(unit);
	}
}


CSnake::~CSnake()
{
}


void CSnake::showSnake()
{
	for (int i = 0; i < m_iLength; i++)
	{
		m_vecBody[i].show();//չʾ����
	}
}

void CSnake::eraseSnake()
{
	for (int i = 0; i < m_iLength; i++)
	{
		m_vecBody[i].erase();
	}
}//��������

void CSnake::changeDirection(int vkValue)
{	
	switch (vkValue)
	{
	case 'w':    
		if (m_enumCurrentDirection == LEFT || m_enumCurrentDirection == RIGHT)
			m_enumCurrentDirection = UP;
		break;
	case 's':
		if (m_enumCurrentDirection == LEFT || m_enumCurrentDirection == RIGHT) 
			m_enumCurrentDirection = DOWN;
		break;
	case 'a':
		if (m_enumCurrentDirection == UP || m_enumCurrentDirection == DOWN) 
			m_enumCurrentDirection = LEFT;
		break;
	case 'd':
		if (m_enumCurrentDirection == UP || m_enumCurrentDirection == DOWN)
			m_enumCurrentDirection = RIGHT;
		break;
	}
}//��WASDת��Ϊ��������

void CSnake::move()
{
	eraseSnake();
	for (int i = m_iLength - 2; i >= 0; i--)
	{
		m_vecBody[i + 1].m_iX = m_vecBody[i].m_iX;
		m_vecBody[i + 1].m_iY = m_vecBody[i].m_iY;//��һ�������������ǰһ�������
	}

	switch (m_enumCurrentDirection)//��ͷ�ı���
	{
	case UP:
		m_vecBody[0].m_iY--;
		break;
	case DOWN:
		m_vecBody[0].m_iY++;
		break;
	case LEFT:
		m_vecBody[0].m_iX--;
		break;
	case RIGHT:
		m_vecBody[0].m_iX++;
		break;
	}

	showSnake();

	Sleep(m_iSpeed);//�ӳٵĺ�����
	//_sleep(m_iSpeed);
}//�ߵ��ƶ�

void CSnake::growup()
{
	CUnit unit(0, 0, m_cPic);
	m_vecBody.push_back(unit);//ƨ�ɺ����һ��ģ��
	m_iLength++;
}//�߳�ʳ���ı���

bool CSnake::eatFood(CFood *pFood)
{
	if (m_vecBody[0].m_iX == pFood->m_iX && m_vecBody[0].m_iY == pFood->m_iY)//��ͷ��x,y�������ʳ���
	{
		growup();
		return true;
	}
	return false;
}
