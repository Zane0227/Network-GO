#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

//======ͷ�ļ���ֻ��������

extern bool gameStart,gameOver, gameQuit;
extern int Window_width, Window_height, stageWidth, stageHeight;
extern int TurnsCount;
extern int TurnsCountMax;
extern sf::Vector2i originPoint;	//���̵�[0,0]������
extern sf::Vector2i mousePosition;	//�������

extern int crossPoint[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
extern int crossPointPre1[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
extern int crossPointPre2[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
extern int crossPointTemp[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
extern int visitedPoint[19][19];
extern int livePoint[19][19];
extern int blackScore;
extern int whiteScore;
extern int isPVE;


extern sf::RenderWindow window;