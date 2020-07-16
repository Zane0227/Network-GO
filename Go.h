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
		tLocal,//������Ϸ
		tLocalSel,
		tOnline,//������Ϸ
		tOnlineSel,
		tExit,//�˳���Ϸ
		tExitSel,
		tButtonRestart,//���¿���
		tButtonRestartSel,
		tButtonRegret,//����
		tButtonRegretSel,
		tButtonIsWin,//����
		tButtonIsWinSel,
		tButtonPVP,//����
		tButtonPVPSel,
		tButtonPVE,//�˻�
		tButtonPVESel,
		tWinBlack,
		tWinWhite;

	sf::Sprite	sBackGround,
		sChooseBack,
		sWhiteStone,
		sBlackStone,
		sLocal,//������Ϸ
		sLocalSel,
		sOnline,//������Ϸ
		sOnlineSel,
		sExit,//�˳�
		sExitSel,
		sButtonRestart,//���¿���
		sButtonRegret,//����
		sButtonIsWin,//����
		sButtonPVP,//����
		sButtonPVE,//�˻�
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

