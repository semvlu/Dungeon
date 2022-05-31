#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>
#include <string>
#include "Position.h"
class Hero;
class Creature;
class Trigger;

// Constent value
const std::string GWALL = "O";
const std::string GNOTHING = " ";

// Board size
const int GWIDTH = 10;
const int GHEIGHT = 10;

// Destinated game loop period
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

std::string     gBoard[][GWIDTH];
extern Hero		gHero;
extern Creature gCreature;
extern Trigger  gTrigger;

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough�A�Q�� call-by-referce �N�p��o�쪺��V�^��
bool canSee(Position cPos, Position hPos, Position& pos2);

// �w�q���ؿ�J���O�P�����}�Cindex
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	INVALID,
};

// function declare
// ������J���A
void keyUpdate(bool key[]);
// �P�_��m�O�_����
bool isPositionValid(Position& loc);

// Initial board
void initBoard(void);

// ��X����
void draw(void);

// ��X������T
void drawInfo(void);

// �{���D�X�ʨ禡
void update(bool key[]);

#endif //__FUNCTIONS_H__