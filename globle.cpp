#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

//======��ͷ�ļ�������ȫ�ֱ������ж��壡������

bool gameStart,gameOver, gameQuit;
int Window_width, Window_height, stageWidth, stageHeight;
int TurnsCount;
int TurnsCountMax;
sf::Vector2i originPoint;	//���̵�[0,0]������
sf::Vector2i mousePosition;	//�������
int crossPoint[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
int crossPointPre1[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
int crossPointPre2[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
int crossPointTemp[19][19];		//��������ݣ�0Ϊ�գ���Ϊ1����Ϊ-1
int visitedPoint[19][19];
int livePoint[19][19];
int blackScore;
int whiteScore;
int isPVE;
sf::RenderWindow window;

