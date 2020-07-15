#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

//======头文件中只进行声明

extern bool gameStart,gameOver, gameQuit;
extern int Window_width, Window_height, stageWidth, stageHeight;
extern int TurnsCount;
extern int TurnsCountMax;
extern sf::Vector2i originPoint;	//棋盘的[0,0]点坐标
extern sf::Vector2i mousePosition;	//鼠标坐标

extern int crossPoint[19][19];		//交叉点数据，0为空，白为1，黑为-1
extern int crossPointPre1[19][19];		//交叉点数据，0为空，白为1，黑为-1
extern int crossPointPre2[19][19];		//交叉点数据，0为空，白为1，黑为-1
extern int crossPointTemp[19][19];		//交叉点数据，0为空，白为1，黑为-1
extern int visitedPoint[19][19];
extern int livePoint[19][19];
extern int blackScore;
extern int whiteScore;
extern int isPVE;


extern sf::RenderWindow window;