#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

//======对头文件声明的全局变量进行定义！！！！

bool gameStart,gameOver, gameQuit;
int Window_width, Window_height, stageWidth, stageHeight;
int TurnsCount;
int TurnsCountMax;
sf::Vector2i originPoint;	//棋盘的[0,0]点坐标
sf::Vector2i mousePosition;	//鼠标坐标
int crossPoint[19][19];		//交叉点数据，0为空，白为1，黑为-1
int crossPointPre1[19][19];		//交叉点数据，0为空，白为1，黑为-1
int crossPointPre2[19][19];		//交叉点数据，0为空，白为1，黑为-1
int crossPointTemp[19][19];		//交叉点数据，0为空，白为1，黑为-1
int visitedPoint[19][19];
int livePoint[19][19];
int blackScore;
int whiteScore;
int isPVE;
sf::RenderWindow window;

