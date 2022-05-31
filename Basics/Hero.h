#pragma once
#include <string>
#include "Position.h"
#include "main.h"
#include "Trigger.h"
class Hero 
{
private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
	int			sLevel = 1;     // Level
	int			sMaxExp;		// Level update experience
	int			sCurrentExp;	// current exp hero has
	int			blood = 10;

public:
	// Default constructor
	Hero() {
		this->sPos.x = 2;
		this->sPos.y = 3;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 10;
		this->sIcon = 'H';
		this->blood = 10;
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H', int inBlood = 10) {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->blood = inBlood;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H', int inBlood = 10) {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->blood = inBlood;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	void setBlood(int sBlood) { this->blood = sBlood; }

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Set level
	void setLevel(int level) { this->sLevel = level; }

	// Set exp
	void setExp(int exp) { this->sCurrentExp = exp; }

	// Set MaxExp
	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Get position
	Position getPos(void) { return this->sPos; }
	int getPosX(){ return this->sPos.x; }
	int getPosY(){ return this->sPos.y; }


	int getBlood() { return this->blood; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get level
	int getLevel(void) { return this->sLevel; }

	// Get Exp
	int getExp(void) { return this->sCurrentExp; }

	// Get Max
	int getMaxExp(void) { return this->sMaxExp; }

	// Incrementally move the elements 
	void move(int x, int y) {
		// Compute the next position
		Position next;
		next.x = this->sPos.x + x;
		next.y = this->sPos.y + y;

		if (isPositionValid(next))
			this->sPos = next;
		else
			std::cout << "Invalid location\n";
	}

	// Calculate Gain of EXP
	void gainEXP(int points) 
	{
		// Implement Gain of EXP
		/*Please implement your code here*/
		setExp( getExp() + points );
		if (getExp() == 10)
		{
			setLevel(getLevel() + 1);
			setExp(0);
		}
		/************************************************************************/
	}
	void damage(int points) 
	{
		// Implement Damage done to Hero
		/*Please implement your code here*/
		setBlood(getBlood() - points);
		/************************************************************************/
	}
};
