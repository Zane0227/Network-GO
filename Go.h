#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

#define	GRIDSIZE 30

class Go
{

private:
	sf::Texture tBackGround,
		tChooseBack,
		tWhiteStone,
		tBlackStone,
		tLocal,//本地游戏
		tLocalSel,
		tOnline,//在线游戏
		tOnlineSel,
		tExit,//退出游戏
		tExitSel,
		tButtonRestart,//重新开局
		tButtonRestartSel,
		tButtonRegret,//悔棋
		tButtonRegretSel,
		tButtonIsWin,//结算
		tButtonIsWinSel,
		tButtonPVP,//人人
		tButtonPVPSel,
		tButtonPVE,//人机
		tButtonPVESel,
		tWinBlack,
		tWinWhite;

	sf::Sprite	sBackGround,
		sChooseBack,
		sWhiteStone,
		sBlackStone,
		sLocal,//本地游戏
		sLocalSel,
		sOnline,//在线游戏
		sOnlineSel,
		sExit,//退出
		sExitSel,
		sButtonRestart,//重新开局
		sButtonRegret,//悔棋
		sButtonIsWin,//结算
		sButtonPVP,//人人
		sButtonPVE,//人机
		sWinBlack,
		sWinWhite;

	sf::IntRect rectButtonRestart,
		rectButtonRegret,
		rectButtonIsWin,
		rectButtonPVP,
		rectButtonPVE,
		recButtonLocal,
		recButtonOnline,
		recButtonExit;

public:
	Go();
	~Go();
	//sf::RenderWindow window;

	void Run();

	void Initial();
	void LoadMediaData();

	void Input();
	void LBtnDown(sf::Vector2i mPosition);


	void Logic();
	int Drop(int ,int);
	void AIDrop();
	int dropStone(int,int);
	int checkPoint(int, int);
	int checkReverse(int,int);
	void checkAll();
	void flushAll();
	void resetVisitedPont();
	void regretChess();
	void isWin();


	void Draw();
	void DrawEnd();
	void DrawChooseButton();
	void DrawButton();
	void drawBlackWin();
	void drawWhiteWin();
};

