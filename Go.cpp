#include "globle.h"
#include "Go.h"
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>
#include <stdlib.h>

#define	GRIDSIZE 30

//���캯����������
Go::Go()
{
	srand((unsigned)time(NULL));
	Window_width = 1000;
	Window_height = 675;
	window.create(sf::VideoMode(Window_width, Window_height), L"Go by �Ľ���", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);  //����֡Ƶ
}
//����������û��
Go::~Go()
{
}

//=================================  ��ʼ��  ===================================//

//��ʼ������
void Go::Initial()
{
	gameStart = true;
	gameOver = false;
	gameQuit = false;
	isPVE = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			crossPoint[i][j] = 0;
			crossPointPre1[i][j] = 0;
			crossPointPre2[i][j] = 0;
			crossPointTemp[i][j] = 0;
			visitedPoint[i][j] = 0;
			livePoint[i][j] = 1;
		}
	}


	originPoint.x = 60;
	originPoint.y = 60;
	TurnsCount = 0;
	blackScore = 0;
	whiteScore = 0;
 
	LoadMediaData();
}
//�����ز�
void Go::LoadMediaData()
{
	//���ر���
	if (!tBackGround.loadFromFile("data/images/����.jpg"))
		std::cout << "����ͼû���ҵ�" << std::endl;
	sBackGround.setTexture(tBackGround);

	//�趨���Ӿ���
	if (!tWhiteStone.loadFromFile("data/images/white_stone.png"))
		std::cout << "����ͼû���ҵ�" << std::endl;
	sWhiteStone.setTexture(tWhiteStone);
	sWhiteStone.setOrigin(15, 15);

	//�趨���Ӿ���
	if (!tBlackStone.loadFromFile("data/images/black_stone.png"))
		std::cout << "����ͼû���ҵ�" << std::endl;
	sBlackStone.setTexture(tBlackStone);
	sBlackStone.setOrigin(15, 15);

	//�������¿�ʼ��ť
	if (!tButtonRestart.loadFromFile("data/images/���¿�ʼ.jpg"))
		std::cout << "���¿�ʼ��ťͼû���ҵ�" << std::endl;
	if (!tButtonRestartSel.loadFromFile("data/images/���¿�ʼѡ��.jpg"))
		std::cout << "���¿�ʼѡ�а�ťͼû���ҵ�" << std::endl;
	sButtonRestart.setTexture(tButtonRestart);

	//���ػ��尴ť
	if (!tButtonRegret.loadFromFile("data/images/����.jpg"))
		std::cout << "���尴ťͼû���ҵ�" << std::endl;
	if (!tButtonRegretSel.loadFromFile("data/images/����ѡ��.jpg"))
		std::cout << "����ѡ�а�ťͼû���ҵ�" << std::endl;
	sButtonRegret.setTexture(tButtonRegret);

	//����ʤ���жϰ�ť
	if (!tButtonIsWin.loadFromFile("data/images/�ж�ʤ��.jpg"))
		std::cout << "ʤ���жϰ�ťͼû���ҵ�" << std::endl;
	if (!tButtonIsWinSel.loadFromFile("data/images/�ж�ʤ��ѡ��.jpg"))
		std::cout << "ʤ���ж�ѡ�а�ťͼû���ҵ�" << std::endl;
	sButtonIsWin.setTexture(tButtonIsWin);

	//�����˻����İ�ť
	if (!tButtonPVE.loadFromFile("data/images/�˻�����.jpg"))
		std::cout << "�˻����İ�ťͼû���ҵ�" << std::endl;
	if (!tButtonPVESel.loadFromFile("data/images/�˻�����ѡ��.jpg"))
		std::cout << "�˻�����ѡ�а�ťͼû���ҵ�" << std::endl;
	sButtonPVE.setTexture(tButtonPVE);

	//�������˶��İ�ť
	if (!tButtonPVP.loadFromFile("data/images/���˶���.jpg"))
		std::cout << "���˶��İ�ťͼû���ҵ�" << std::endl;
	if (!tButtonPVPSel.loadFromFile("data/images/���˶���ѡ��.jpg"))
		std::cout << "���˶���ѡ�а�ťͼû���ҵ�" << std::endl;
	sButtonPVP.setTexture(tButtonPVP);

	//���غ���ʤ��
	if (!tWinBlack.loadFromFile("data/images/����ʤ��.png"))
		std::cout << "����ʤ��ͼû���ҵ�" << std::endl;
	sWinBlack.setTexture(tWinBlack);

	//���ذ���ʤ��
	if (!tWinWhite.loadFromFile("data/images/����ʤ��.png"))
		std::cout << "����ʤ��ͼû���ҵ�" << std::endl;
	sWinWhite.setTexture(tWinWhite);

}

//=================================  ����  ===================================//

//��ȡ�����¼�
void Go::Input()
{
	sf::Event event;//event types ����Window��Keyboard��Mouse��Joystick��4����Ϣ
					//ͨ��  bool Window :: pollEvent��sf :: Event��event�� �Ӵ���˳��ѯ�ʣ� polled ���¼��� 
					//�����һ���¼��ȴ������ú���������true�������¼���������䣨filled���¼����ݡ� 
					//������ǣ���ú�������false�� ͬ����Ҫ����Ҫע�⣬һ�ο����ж���¼�; ������Ǳ���ȷ������ÿ�����ܵ��¼��� 

	while (window.pollEvent(event))
	{

		//������Ͻǹر�
		if (event.type == sf::Event::Closed)
		{
			window.close();		//���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		//����ESC��
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();		//���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}

		mousePosition.x = sf::Mouse::getPosition(window).x;
		mousePosition.y = sf::Mouse::getPosition(window).y;

		//���ͷ�
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (!gameOver)
			{
				
				Go::LBtnDown(mousePosition);

				//
				if (rectButtonRestart.contains(event.mouseButton.x, event.mouseButton.y))
				{
					Initial();
				}
				if (rectButtonRegret.contains(mousePosition.x, mousePosition.y))
				{
					regretChess();
				}
				if (rectButtonIsWin.contains(mousePosition.x, mousePosition.y))
				{
					isWin();
				}
				if (rectButtonPVP.contains(mousePosition.x, mousePosition.y))
				{
					
					Initial();
					isPVE = 0;
				}
				if (rectButtonPVE.contains(mousePosition.x, mousePosition.y))
				{
					Initial();
					isPVE = 1;
				}
			}
			else
			{
				Initial();
			}
		}

		//�ƹ����¿�ʼ��ť����
		if (rectButtonRestart.contains(mousePosition.x, mousePosition.y))
		{
			sButtonRestart.setTexture(tButtonRestartSel);
		}
		else
		{
			sButtonRestart.setTexture(tButtonRestart);
		}
		//�ƹ����尴ť����
		if (rectButtonRegret.contains(mousePosition.x, mousePosition.y))
		{
			sButtonRegret.setTexture(tButtonRegretSel);
		}
		else
		{
			sButtonRegret.setTexture(tButtonRegret);
		}
		//�ƹ��˻����İ�ť����
		if (rectButtonPVE.contains(mousePosition.x, mousePosition.y))
		{
			sButtonPVE.setTexture(tButtonPVESel);
		}
		else
		{
			sButtonPVE.setTexture(tButtonPVE);
		}
		//�ƹ����˶��İ�ť����
		if (rectButtonPVP.contains(mousePosition.x, mousePosition.y))
		{
			sButtonPVP.setTexture(tButtonPVPSel);
		}
		else
		{
			sButtonPVP.setTexture(tButtonPVP);
		}
		//�ƹ����㰴ť����
		if (rectButtonIsWin.contains(mousePosition.x, mousePosition.y))
		{
			sButtonIsWin.setTexture(tButtonIsWinSel);
		}
		else
		{
			sButtonIsWin.setTexture(tButtonIsWin);
		}
	}
}

void Go::LBtnDown(sf::Vector2i mPosition)
{
	int x, y;

	//����
	if (	(mPosition.x > originPoint.x - GRIDSIZE / 2)
			&& (mPosition.y > originPoint.y - GRIDSIZE / 2)
			&& (mPosition.x < originPoint.x + GRIDSIZE * 19.5)
			&& (mPosition.y < originPoint.y + GRIDSIZE * 19.5)
		)
	{
		x = (mPosition.x - originPoint.x + GRIDSIZE / 2) / GRIDSIZE;
		y = (mPosition.y - originPoint.y + GRIDSIZE / 2) / GRIDSIZE;

		if (isPVE == 0) {
			Drop(x, y);
		}
		else
		{
			if(Drop(x, y))
				AIDrop();
		}



	}


}

//=================================  �߼�  ===================================//
void Go::Logic()
{
}

//����
int Go::Drop(int x,int y)
{
	//����ǰ����������
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			crossPointTemp[i][j] = crossPoint[i][j];
			//crossPointPre2[i][j] = crossPointPre1[i][j];
			//crossPointPre1[i][j] = crossPoint[i][j];
		}
	}

	if (!dropStone(x, y))
		return 0;

	//�µ���һ������
	if (checkPoint(x, y) == 0)
	{
		resetVisitedPont();
		//����Ƿ��ܷ���
		if (checkReverse(x, y))
		{
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					crossPointPre2[i][j] = crossPointPre1[i][j];
					crossPointPre1[i][j] = crossPointTemp[i][j];
				}
			}
			flushAll();
			TurnsCount--;//Ϊ���油����ɱ������

			//���ط���ʱ��ɱ������
			int stone;
			stone = TurnsCount % 2 == 0 ? -1 : 1;
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (crossPointPre1[i][j] == stone)
						crossPoint[i][j] = stone;
				}
			}
			dropStone(x, y);
			TurnsCountMax = TurnsCount;


			return 1;
		}

		TurnsCount--;
		TurnsCountMax = TurnsCount;
		crossPoint[x][y] = 0;

		resetVisitedPont();
		return 0;
	}
	//�µĲ������塪>���ȫ��
	else
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				crossPointPre2[i][j] = crossPointPre1[i][j];
				crossPointPre1[i][j] = crossPointTemp[i][j];
			}
		}
		TurnsCountMax = TurnsCount;
		resetVisitedPont();
		flushAll();
		return 1;
	}
}

//1�����ӳɹ�
int Go::dropStone(int x,int y)
{
	//����غ�
	if (TurnsCount % 2 == 0 && crossPoint[x][y] == 0)
	{
		crossPoint[x][y] = -1;
		TurnsCount++;
		return 1;
	}
	//����غ�
	if (TurnsCount % 2 == 1 && crossPoint[x][y] == 0)
	{
		crossPoint[x][y] = 1;
		TurnsCount++;
		return 1;
	}

	return 0;
}

//����1�ǻ��壬����0������
int Go::checkPoint(int x, int y)
{
	visitedPoint[x][y] = 1;

	//����ǿյ㣬ֱ�ӷ�������
	if (crossPoint[x][y] == 0)
		return 0;

	

	sf::Vector2i up, down, left, right;


	left.x = x - 1 > -1 ? x - 1 : x;
	left.y = y ;
	right.x = x + 1 < 19 ? x + 1 : x;
	right.y = y;
	up.x = x;
	up.y = y - 1 > -1 ? y - 1 : y;
	down.x = x;
	down.y = y + 1 < 19 ? y + 1 : y;

	//����յ�
	if (crossPoint[up.x][up.y] == 0
		||crossPoint[down.x][down.y] == 0
		||crossPoint[left.x][left.y] == 0
		||crossPoint[right.x][right.y] == 0
		)
		{
			return 1;
		}

	//����
	if (crossPoint[x][y] == 1)
	{
		if (crossPoint[up.x][up.y] == 1 && visitedPoint[up.x][up.y] == 0)
		{
			if (checkPoint(up.x, up.y) == 1)
				return 1;
		}
		if (crossPoint[down.x][down.y] == 1 && visitedPoint[down.x][down.y] == 0)
		{
			if (checkPoint(down.x, down.y) == 1)
				return 1;
		}
		if (crossPoint[left.x][left.y] == 1 && visitedPoint[left.x][left.y] == 0)
		{
			if (checkPoint(left.x, left.y) == 1)
				return 1;
		}
		if (crossPoint[right.x][right.y] == 1 && visitedPoint[right.x][right.y] == 0)
		{
			if (checkPoint(right.x, right.y) == 1)
				return 1;
		}
		return 0;
	}

	//����
	if (crossPoint[x][y] == -1)
	{
		if (crossPoint[up.x][up.y] == -1 && visitedPoint[up.x][up.y] == 0)
		{
			if (checkPoint(up.x, up.y) == 1)
				return 1;
		}
		if (crossPoint[down.x][down.y] == -1 && visitedPoint[down.x][down.y] == 0)
		{
			if (checkPoint(down.x, down.y) == 1)
				return 1;
		}
		if (crossPoint[left.x][left.y] == -1 && visitedPoint[left.x][left.y] == 0)
		{
			if (checkPoint(left.x, left.y) == 1)
				return 1;
		}
		if (crossPoint[right.x][right.y] == -1 && visitedPoint[right.x][right.y] == 0)
		{
			if (checkPoint(right.x, right.y) == 1)
				return 1;
		}
		return 0;
	}
	

	/*�������
	std::cout << "up.x  "<< up.x << std::endl;
	std::cout << "up.y  " << up.y << std::endl;
	std::cout << "left.x  " << left.x << std::endl;
	std::cout << "left.y  " << left.y << std::endl;
	std::cout << "down.x  " << down.x << std::endl;
	std::cout << "down.y  " << down.y << std::endl;
	std::cout << "right.x  " << right.x << std::endl;
	std::cout << "right.y  " << right.y << std::endl;
	*/


}

//����Ƿ��ܷ��ԣ���1��0
int Go::checkReverse(int x, int y)
{
	int f = 0;
	sf::Vector2i up, down, left, right;

	left.x = x - 1 > -1 ? x - 1 : x;
	left.y = y;
	right.x = x + 1 < 19 ? x + 1 : x;
	right.y = y;
	up.x = x;
	up.y = y - 1 > -1 ? y - 1 : y;
	down.x = x;
	down.y = y + 1 < 19 ? y + 1 : y;

	//��ǰ���ǰ���
	if (crossPoint[x][y] == 1)
	{
		if (f == 0 &&
			crossPoint[left.x][left.y] == -1 && 
			checkPoint(left.x, left.y) == 0) 
		{
			f = 1;
		}
		resetVisitedPont();

		if (f == 0 &&
			crossPoint[right.x][right.y] == -1 && 
			checkPoint(right.x, right.y) == 0)
		{
			f = 1;
		}
		resetVisitedPont();

		if (f == 0 &&
			crossPoint[up.x][up.y] == -1 && 
			checkPoint(up.x, up.y) == 0)
		{
			f = 1;
		}
		resetVisitedPont();

		if (f == 0 &&
			crossPoint[down.x][down.y] == -1 && 
			checkPoint(down.x, down.y) == 0)
		{
			f = 1;
		}
		resetVisitedPont();

	}

	//��ǰ���Ǻ���
	if (crossPoint[x][y] == -1)
	{
		if (f == 0 &&
			crossPoint[left.x][left.y] == 1 && 
			checkPoint(left.x, left.y) == 0)
		{
			resetVisitedPont();
			f = 1;
		}
		if (f == 0 &&
			crossPoint[right.x][right.y] == 1 && 
			checkPoint(right.x, right.y) == 0)
		{
			resetVisitedPont();
			f = 1;
		}
		if (f == 0 &&
			crossPoint[up.x][up.y] == 1 && 
			checkPoint(up.x, up.y) == 0)
		{
			resetVisitedPont();
			f = 1;
		}
		if (f == 0 &&
			crossPoint[down.x][down.y] == 1 && 
			checkPoint(down.x, down.y) == 0)
		{
			resetVisitedPont();
			f = 1;
		}
	}
	return f;

}

//����ÿ���������״̬
void Go::checkAll()
{
	//ѭ��ÿһ�������
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//������ӵ�����
			livePoint[i][j] = checkPoint(i, j);
			//ÿ�μ����һ���㣬����Ҫ����
			resetVisitedPont();
		}
	}
}

//���Ӻ����ÿ������������
void Go::flushAll()
{
	
	checkAll();

	
	//�����ɺ�ˢ�����̲���
	//�����浱ǰ�غ�
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (livePoint[i][j] == 0)
				crossPoint[i][j] = 0;
		}
	}
}

//���÷��ʵ�
void Go::resetVisitedPont()
{
	//ÿ�μ����һ���㣬����Ҫ����
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			visitedPoint[i][j] = 0;
		}
	}
}

//����
void Go::regretChess()
{
	

	//������峬���������ϣ�������
	if (TurnsCount == TurnsCountMax - 2 || isPVE)
	{
		return;
	}


	TurnsCount--;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			crossPoint[i][j] = crossPointPre1[i][j];
			crossPointPre1[i][j] = crossPointPre2[i][j];
		}
	}
	
}

//���ս���
void Go::isWin()
{
	gameOver = true;


	//���ӷ�
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//�յ�
			if (crossPoint[i][j] == 0)
			{
				sf::Vector2i up, down, left, right;

				left.x = i - 1 > -1 ? i - 1 : i;
				left.y = j;
				right.x = i + 1 < 19 ? i + 1 : i;
				right.y = j;
				up.x = i;
				up.y = j - 1 > -1 ? j - 1 : j;
				down.x = i;
				down.y = j + 1 < 19 ? j + 1 : j;

				if (crossPoint[up.x][up.y] == 1
					&& crossPoint[down.x][down.y] == 1
					&& crossPoint[left.x][left.y] == 1
					&& crossPoint[right.x][right.y] == 1)
				{
					whiteScore++;
				}
				if (crossPoint[up.x][up.y] == -1
					&& crossPoint[down.x][down.y] == -1
					&& crossPoint[left.x][left.y] == -1
					&& crossPoint[right.x][right.y] == -1)
				{
					blackScore++;
				}
			}

			if (crossPoint[i][j] == 1)
				whiteScore++;
			if (crossPoint[i][j] == -1)
				blackScore++;

		}
	}

	

	std::cout << "����ռ�أ�" << blackScore<< std::endl;
	std::cout << "����ռ�أ�" << whiteScore<< std::endl;


}

//�������°��壬�����µ�x,y
void Go::AIDrop()
{
	int qi=0;
	int qiMin;
	int dropX,dropY;
	int a;

	if (TurnsCount < 16)
	{
		do {
			dropX = rand() % 19;
			dropY = rand() % 19;
			a = Drop(dropX, dropY);
		} while (a == 0);
		return;
	}

	//�������������ĺ�����Χ
	for (qiMin = 1; qiMin <= 4; qiMin++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				//��������
				if (crossPoint[i][j] == -1)
				{

					//��ȡ������������
					sf::Vector2i up, down, left, right;
					left.x = i - 1 > -1 ? i - 1 : i;
					left.y = j;
					right.x = i + 1 < 19 ? i + 1 : i;
					right.y = j;
					up.x = i;
					up.y = j - 1 > -1 ? j - 1 : j;
					down.x = i;
					down.y = j + 1 < 19 ? j + 1 : j;

					//���㵱ǰ������ܱ���
					if (crossPoint[up.x][up.y] == 0)
					{
						qi++;
					}
					if (crossPoint[down.x][down.y] == 0)
					{
						qi++;
					}
					if (crossPoint[left.x][left.y] == 0)
					{
						qi++;
					}
					if (crossPoint[right.x][right.y] == 0)
					{
						qi++;
					}

					//�ú�������������С������ÿһ����������
					if (qi == qiMin)
					{
						if (crossPoint[up.x][up.y] == 0)
						{
							dropX = up.x;
							dropY = up.y;

							if (Drop(dropX, dropY))
								return;
						}
						if (crossPoint[down.x][down.y] == 0)
						{
							dropX = down.x;
							dropY = down.y;
							if (Drop(dropX, dropY))
								return;
						}
						if (crossPoint[left.x][left.y] == 0)
						{
							dropX = left.x;
							dropY = left.y;
							if (Drop(dropX, dropY))
								return;
						}
						if (crossPoint[right.x][right.y] == 0)
						{
							dropX = right.x;
							dropY = right.y;
							if (Drop(dropX, dropY))
								return;
						}
					}
					qi = 0;
				}
			}
		}
	}

	//�޷����ں�����Χ�Ļ�
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//�����յ�
			if (crossPoint[i][j] == 0)
			{

				if (Drop(i, j))
					return;
				
			}
		}
	}

	//���²��ˣ���Ϸ����
	gameOver = true;
	
}

//=================================  ����  ===================================//
void Go::Draw()
{
	window.clear();
	// ==================��Ϸ��û��ʼ��ѡ�����߻�����==================//
	if (!gameStart)
	{

	}
	// ==================��Ϸ��ʼ==================//
	else
	{
		sBackGround.setPosition(0, 0);
		window.draw(sBackGround);

		// ���ư�ť
		DrawButton();

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (crossPoint[i][j] == 1)
				{
					sWhiteStone.setPosition(originPoint.x + i * GRIDSIZE, originPoint.y + j * GRIDSIZE);
					window.draw(sWhiteStone);
				}
				if (crossPoint[i][j] == -1)
				{
					sBlackStone.setPosition(originPoint.x + i * GRIDSIZE, originPoint.y + j * GRIDSIZE);
					window.draw(sBlackStone);
				}
			}
		}

		if (gameOver)
			DrawEnd();
	}

	// ������̨
	window.display();
}

void Go::DrawButton()
{
	//�������¿�ʼ��ť
	sButtonRestart.setPosition(650, 480);
	rectButtonRestart.left = 650;
	rectButtonRestart.top = 480;
	rectButtonRestart.height = 50;
	rectButtonRestart.width = 100;
	window.draw(sButtonRestart);

	//���ƻ��尴ť
	sButtonRegret.setPosition(800, 480);
	rectButtonRegret.left = 800;
	rectButtonRegret.top = 480;
	rectButtonRegret.height = 50;
	rectButtonRegret.width = 100;
	window.draw(sButtonRegret);

	//�����ж�ʤ����ť
	sButtonIsWin.setPosition(725, 600);
	rectButtonIsWin.left = 725;
	rectButtonIsWin.top = 600;
	rectButtonIsWin.height = 50;
	rectButtonIsWin.width = 100;
	window.draw(sButtonIsWin);

	//�����˻����İ�ť
	sButtonPVE.setPosition(650, 540);
	rectButtonPVE.left = 650;
	rectButtonPVE.top = 540;
	rectButtonPVE.height = 50;
	rectButtonPVE.width = 100;
	window.draw(sButtonPVE);

	//�������˰�ť
	sButtonPVP.setPosition(800, 540);
	rectButtonPVP.left = 800;
	rectButtonPVP.top = 540;
	rectButtonPVP.height = 50;
	rectButtonPVP.width = 100;
	window.draw(sButtonPVP);

}

void Go::drawBlackWin()
{
	std::cout << "����Ӯ��" << std::endl;
	sWinBlack.setPosition(300, 300);
	window.draw(sWinBlack);
}

void Go::drawWhiteWin()
{
	std::cout << "����Ӯ��" << std::endl;
	sWinWhite.setPosition(300, 300);
	window.draw(sWinWhite);
}

void Go::DrawEnd()
{
		if (blackScore > whiteScore)
		{
			drawBlackWin();
		}
		else
		{
			drawWhiteWin();
		}

}
//=================================  ����  ===================================//
void Go::Run()
{
	do
	{

		Initial();

		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();
		}

		Draw();
		Sleep(2000);

	} while (!gameQuit);
}


