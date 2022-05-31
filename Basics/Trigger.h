#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Hero.h"

// Trigger Class
class Trigger
{
private:
	Position tPos{ 8, 7 };
	char icon = 'T';
	int exp = 2;
public:
	Trigger()
	{
		tPos.x = 8;
		tPos.y = 7;
		icon = 'T';
	}
	Trigger(int x, int y, int sExp)
	{
		tPos.x = x;
		tPos.y = y;
		icon = 'T';
		exp = sExp;
	}

	Position getPos(void) { return this->tPos; }
	int getPosX() { return this->tPos.x; }
	int getPosY() { return this->tPos.y; }
	char getIcon(void) { return this->icon; }
	int getExpAmount() { return this->exp; }



};