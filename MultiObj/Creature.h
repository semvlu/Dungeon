#pragma once
#include <string>
#include <vector>
#include "Position.h"
#include "Hero.h"
#include "main.h"
using namespace std;
class Creature {//creature class 
private:
	Position	sPos;			// Creature position
	char sIcon;			// Creature icon
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = 'C';
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

public:
	void update(Position hPos) {
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
			int randNum = rand() % 4;
			if (randNum == 0)
			{
				Position test = sPos;
				test.x += dir.x;
				test.y += dir.y;
				if (isPositionValid(test))
				{
					this->sPos.x += dir.x;
					this->sPos.y += dir.y;
				}
			}
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = getIcon();
			int randNum = rand() % 4;
			if (randNum == 0)
			{
				Position test = sPos;
				test.x += 1;
				if (isPositionValid(test))
				{
					this->sPos.x += 1;
				}
				else
				{
					this->sPos.x -= 1;
				}
			}
			if (randNum == 1)
			{
				Position test = sPos;
				test.x -= 1;
				if (isPositionValid(test))
				{
					this->sPos.x -= 1;
				}
				else
				{
					this->sPos.x += 1;
				}
			}
			if (randNum == 2)
			{
				Position test = sPos;
				test.y += 1;
				if (isPositionValid(test))
				{
					this->sPos.y += 1;
				}
				else
				{
					this->sPos.y -= 1;
				}
			}
			if (randNum == 3)
			{
				Position test = sPos;
				test.y -= 1;
				if (isPositionValid(test))
				{
					this->sPos.y -= 1;
				}
				else
				{
					this->sPos.y += 1;
				}
			}
		}
	}
};

class Devil : public Creature
{
public:
	Devil() : Creature(){}
	Devil(char _icon)
	{
		setPos(1, 1);
		setIcon(_icon);
	}
	Devil(int x, int y, char _icon)
	{
		setPos(x, y);
		setIcon(_icon);
	}

	void cross(Hero h) // damage hero in the region cross
	{
		Position hPos = h.getPos();
		Position dPos = getPos();
		if (dPos.x + 3 >= hPos.x || dPos.x - 3 <= hPos.x || dPos.y + 3 >= hPos.y || dPos.y - 3 <= hPos.y)
		{
			if (dPos.x == hPos.x)
				h.damage(abs(dPos.y - hPos.y));
			else if (dPos.y == hPos.y)
				h.damage(abs(dPos.x - hPos.x));
		}
	}
};

class Witch : public Creature
{
public:
	Witch() : Creature() {}
	Witch(char _icon)
	{
		setPos(1, 1);
		setIcon(_icon);
	}
	Witch(int x, int y, char _icon)
	{
		setPos(x, y);
		setIcon(_icon);
	}

	void fly(Hero h) // fly to hero
	{
		Position hPos = h.getPos();
		int r = rand();
		if (rand() % 5 == 3)
		{
			if (r % 2 == 0)
				setPos(hPos.x + 1, getPos().y);
			else
				setPos(getPos().x, hPos.y - 1);
		}
	}

	void seduce(Hero h) // h.sLevel - 1
	{
		Position hPos = h.getPos();
		if (abs(getPos().x - hPos.x) <= 2 || abs(getPos().y - hPos.y) <= 2)
			h.setLevel(h.getLevel() - 1);
	}
};