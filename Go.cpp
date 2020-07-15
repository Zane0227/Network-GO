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

//构造函数创建窗口
Go::Go()
{
	srand((unsigned)time(NULL));
	Window_width = 1000;
	Window_height = 675;
	window.create(sf::VideoMode(Window_width, Window_height), L"Go by 夏健潇", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);  //窗口帧频
}
//析构函数还没用
Go::~Go()
{
}

//=================================  初始化  ===================================//

//初始化变量
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
//加载素材
void Go::LoadMediaData()
{
	//加载背景
	if (!tBackGround.loadFromFile("data/images/棋盘.jpg"))
		std::cout << "背景图没有找到" << std::endl;
	sBackGround.setTexture(tBackGround);

	//设定白子精灵
	if (!tWhiteStone.loadFromFile("data/images/white_stone.png"))
		std::cout << "白子图没有找到" << std::endl;
	sWhiteStone.setTexture(tWhiteStone);
	sWhiteStone.setOrigin(15, 15);

	//设定黑子精灵
	if (!tBlackStone.loadFromFile("data/images/black_stone.png"))
		std::cout << "黑子图没有找到" << std::endl;
	sBlackStone.setTexture(tBlackStone);
	sBlackStone.setOrigin(15, 15);

	//加载重新开始按钮
	if (!tButtonRestart.loadFromFile("data/images/重新开始.jpg"))
		std::cout << "重新开始按钮图没有找到" << std::endl;
	if (!tButtonRestartSel.loadFromFile("data/images/重新开始选中.jpg"))
		std::cout << "重新开始选中按钮图没有找到" << std::endl;
	sButtonRestart.setTexture(tButtonRestart);

	//加载悔棋按钮
	if (!tButtonRegret.loadFromFile("data/images/悔棋.jpg"))
		std::cout << "悔棋按钮图没有找到" << std::endl;
	if (!tButtonRegretSel.loadFromFile("data/images/悔棋选中.jpg"))
		std::cout << "悔棋选中按钮图没有找到" << std::endl;
	sButtonRegret.setTexture(tButtonRegret);

	//加载胜负判断按钮
	if (!tButtonIsWin.loadFromFile("data/images/判断胜负.jpg"))
		std::cout << "胜负判断按钮图没有找到" << std::endl;
	if (!tButtonIsWinSel.loadFromFile("data/images/判断胜负选中.jpg"))
		std::cout << "胜负判断选中按钮图没有找到" << std::endl;
	sButtonIsWin.setTexture(tButtonIsWin);

	//加载人机对弈按钮
	if (!tButtonPVE.loadFromFile("data/images/人机对弈.jpg"))
		std::cout << "人机对弈按钮图没有找到" << std::endl;
	if (!tButtonPVESel.loadFromFile("data/images/人机对弈选中.jpg"))
		std::cout << "人机对弈选中按钮图没有找到" << std::endl;
	sButtonPVE.setTexture(tButtonPVE);

	//加载人人对弈按钮
	if (!tButtonPVP.loadFromFile("data/images/人人对弈.jpg"))
		std::cout << "人人对弈按钮图没有找到" << std::endl;
	if (!tButtonPVPSel.loadFromFile("data/images/人人对弈选中.jpg"))
		std::cout << "人人对弈选中按钮图没有找到" << std::endl;
	sButtonPVP.setTexture(tButtonPVP);

	//加载黑棋胜利
	if (!tWinBlack.loadFromFile("data/images/黑棋胜利.png"))
		std::cout << "黑棋胜利图没有找到" << std::endl;
	sWinBlack.setTexture(tWinBlack);

	//加载白棋胜利
	if (!tWinWhite.loadFromFile("data/images/白棋胜利.png"))
		std::cout << "白棋胜利图没有找到" << std::endl;
	sWinWhite.setTexture(tWinWhite);

}

//=================================  输入  ===================================//

//获取输入事件
void Go::Input()
{
	sf::Event event;//event types 包括Window、Keyboard、Mouse、Joystick，4类消息
					//通过  bool Window :: pollEvent（sf :: Event＆event） 从窗口顺序询问（ polled ）事件。 
					//如果有一个事件等待处理，该函数将返回true，并且事件变量将填充（filled）事件数据。 
					//如果不是，则该函数返回false。 同样重要的是要注意，一次可能有多个事件; 因此我们必须确保捕获每个可能的事件。 

	while (window.pollEvent(event))
	{

		//点击右上角关闭
		if (event.type == sf::Event::Closed)
		{
			window.close();		//窗口可以移动、调整大小和最小化。但是如果要关闭，需要自己去调用close()函数
			gameQuit = true;
		}
		//按下ESC键
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();		//窗口可以移动、调整大小和最小化。但是如果要关闭，需要自己去调用close()函数
			gameQuit = true;
		}

		mousePosition.x = sf::Mouse::getPosition(window).x;
		mousePosition.y = sf::Mouse::getPosition(window).y;

		//左释放
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

		//移过重新开始按钮动画
		if (rectButtonRestart.contains(mousePosition.x, mousePosition.y))
		{
			sButtonRestart.setTexture(tButtonRestartSel);
		}
		else
		{
			sButtonRestart.setTexture(tButtonRestart);
		}
		//移过悔棋按钮动画
		if (rectButtonRegret.contains(mousePosition.x, mousePosition.y))
		{
			sButtonRegret.setTexture(tButtonRegretSel);
		}
		else
		{
			sButtonRegret.setTexture(tButtonRegret);
		}
		//移过人机对弈按钮动画
		if (rectButtonPVE.contains(mousePosition.x, mousePosition.y))
		{
			sButtonPVE.setTexture(tButtonPVESel);
		}
		else
		{
			sButtonPVE.setTexture(tButtonPVE);
		}
		//移过人人对弈按钮动画
		if (rectButtonPVP.contains(mousePosition.x, mousePosition.y))
		{
			sButtonPVP.setTexture(tButtonPVPSel);
		}
		else
		{
			sButtonPVP.setTexture(tButtonPVP);
		}
		//移过结算按钮动画
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

	//落子
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

//=================================  逻辑  ===================================//
void Go::Logic()
{
}

//落子
int Go::Drop(int x,int y)
{
	//落子前出保存棋盘
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

	//下的是一步死棋
	if (checkPoint(x, y) == 0)
	{
		resetVisitedPont();
		//检查是否能反吃
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
			TurnsCount--;//为下面补回自杀的棋子

			//补回反吃时自杀的棋子
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
	//下的不是死棋—>检查全盘
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

//1是落子成功
int Go::dropStone(int x,int y)
{
	//黑棋回合
	if (TurnsCount % 2 == 0 && crossPoint[x][y] == 0)
	{
		crossPoint[x][y] = -1;
		TurnsCount++;
		return 1;
	}
	//白棋回合
	if (TurnsCount % 2 == 1 && crossPoint[x][y] == 0)
	{
		crossPoint[x][y] = 1;
		TurnsCount++;
		return 1;
	}

	return 0;
}

//返回1是活棋，返回0是死棋
int Go::checkPoint(int x, int y)
{
	visitedPoint[x][y] = 1;

	//如果是空点，直接返回死棋
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

	//计算空地
	if (crossPoint[up.x][up.y] == 0
		||crossPoint[down.x][down.y] == 0
		||crossPoint[left.x][left.y] == 0
		||crossPoint[right.x][right.y] == 0
		)
		{
			return 1;
		}

	//白棋
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

	//黑棋
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
	

	/*输出测试
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

//检查是否能反吃，能1否0
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

	//当前子是白子
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

	//当前子是黑子
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

//计算每个点的生死状态
void Go::checkAll()
{
	//循环每一个交叉点
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//标记棋子的死活
			livePoint[i][j] = checkPoint(i, j);
			//每次检查完一个点，都需要置零
			resetVisitedPont();
		}
	}
}

//落子后更新每个交叉点的死活
void Go::flushAll()
{
	
	checkAll();

	
	//标记完成后，刷新棋盘布局
	//并储存当前回合
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (livePoint[i][j] == 0)
				crossPoint[i][j] = 0;
		}
	}
}

//重置访问点
void Go::resetVisitedPont()
{
	//每次检查完一个点，都需要置零
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			visitedPoint[i][j] = 0;
		}
	}
}

//悔棋
void Go::regretChess()
{
	

	//如果悔棋超过两步以上，则不允许
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

//最终结算
void Go::isWin()
{
	gameOver = true;


	//数子法
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//空地
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

	

	std::cout << "黑棋占地：" << blackScore<< std::endl;
	std::cout << "白棋占地：" << whiteScore<< std::endl;


}

//机器人下白棋，返回下的x,y
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

	//落子在最少气的黑棋周围
	for (qiMin = 1; qiMin <= 4; qiMin++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				//碰到黑棋
				if (crossPoint[i][j] == -1)
				{

					//获取黑棋上下左右
					sf::Vector2i up, down, left, right;
					left.x = i - 1 > -1 ? i - 1 : i;
					left.y = j;
					right.x = i + 1 < 19 ? i + 1 : i;
					right.y = j;
					up.x = i;
					up.y = j - 1 > -1 ? j - 1 : j;
					down.x = i;
					down.y = j + 1 < 19 ? j + 1 : j;

					//计算当前黑棋的周边气
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

					//该黑棋气数等于最小气数，每一步都尝试下
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

	//无法下在黑棋周围的话
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			//碰到空地
			if (crossPoint[i][j] == 0)
			{

				if (Drop(i, j))
					return;
				
			}
		}
	}

	//都下不了，游戏结束
	gameOver = true;
	
}

//=================================  绘制  ===================================//
void Go::Draw()
{
	window.clear();
	// ==================游戏还没开始，选择在线或离线==================//
	if (!gameStart)
	{

	}
	// ==================游戏开始==================//
	else
	{
		sBackGround.setPosition(0, 0);
		window.draw(sBackGround);

		// 绘制按钮
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

	// 绘制舞台
	window.display();
}

void Go::DrawButton()
{
	//绘制重新开始按钮
	sButtonRestart.setPosition(650, 480);
	rectButtonRestart.left = 650;
	rectButtonRestart.top = 480;
	rectButtonRestart.height = 50;
	rectButtonRestart.width = 100;
	window.draw(sButtonRestart);

	//绘制悔棋按钮
	sButtonRegret.setPosition(800, 480);
	rectButtonRegret.left = 800;
	rectButtonRegret.top = 480;
	rectButtonRegret.height = 50;
	rectButtonRegret.width = 100;
	window.draw(sButtonRegret);

	//绘制判断胜负按钮
	sButtonIsWin.setPosition(725, 600);
	rectButtonIsWin.left = 725;
	rectButtonIsWin.top = 600;
	rectButtonIsWin.height = 50;
	rectButtonIsWin.width = 100;
	window.draw(sButtonIsWin);

	//绘制人机对弈按钮
	sButtonPVE.setPosition(650, 540);
	rectButtonPVE.left = 650;
	rectButtonPVE.top = 540;
	rectButtonPVE.height = 50;
	rectButtonPVE.width = 100;
	window.draw(sButtonPVE);

	//绘制人人按钮
	sButtonPVP.setPosition(800, 540);
	rectButtonPVP.left = 800;
	rectButtonPVP.top = 540;
	rectButtonPVP.height = 50;
	rectButtonPVP.width = 100;
	window.draw(sButtonPVP);

}

void Go::drawBlackWin()
{
	std::cout << "黑棋赢了" << std::endl;
	sWinBlack.setPosition(300, 300);
	window.draw(sWinBlack);
}

void Go::drawWhiteWin()
{
	std::cout << "白棋赢了" << std::endl;
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
//=================================  运行  ===================================//
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


