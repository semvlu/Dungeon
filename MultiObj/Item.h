#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Hero.h"

class Item
{
public:
	// Default constructor
	Item()
	{
		sPos.x = 6;
		sPos.y = 7;
		sIcon = 'T';
		sAmount = 5;
	}
	// Setting constructors
	Item(int x, int y, int amt, char icon = 'T')
	{
		sPos.x = x;
		sPos.y = y;
		sAmount = amt;
		sIcon = icon;
	}
	Item(Position& pos, int amt, char icon = 'T')
	{
		sPos = pos;
		sAmount = amt;
		sIcon = icon;
	}

	// functions
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}
	void setIcon(char icon) { this->sIcon = icon; }
	void setAmount(int amt) { this->sAmount = amt; }
	Position getPos(void) { return this->sPos; }
	char getIcon(void) { return this->sIcon; }
	int getAmount(void) { return this->sAmount; }

	virtual void update(Hero& h) { return; }
private:
	Position sPos;
	char sIcon;
	int sAmount;
};


class Trigger : public Item
{
public:
	Trigger() : Item(){}
	Trigger(int x, int y, int amt, char icon = 'T') : Item(x, y, amt, icon) {}
	Trigger(Position& pos, int amt, char icon = 'T'): Item(pos, amt, icon){}

	void trigger(Hero& h) { h.gainEXP(getAmount()); }

	void update(Hero& h) override
	{
		if (this->getPos().x == h.getPos().x && this->getPos().y == h.getPos().y) 
			this->trigger(h);
	}
};

class Trap : public Item
{
public:
	Trap() : Item() {}
	Trap(int x, int y, int amt, char icon = 'T') : Item(x, y, amt, icon) {}
	Trap(Position& pos, int amt, char icon = 'T') : Item(pos, amt, icon) {}

	void fall(Hero& h) { h.setHealth(h.getHealth() - getAmount()); }

	void update(Hero& h) override
	{
		if (this->getPos().x == h.getPos().x && this->getPos().y == h.getPos().y)
			this->fall(h);
	}
};

class Med : public Item
{
public:
	Med() : Item() {}
	Med(int x, int y, int amt, char icon = 'T') : Item(x, y, amt, icon) {}
	Med(Position& pos, int amt, char icon = 'T') : Item(pos, amt, icon) {}

	void cure(Hero& h) { h.setHealth(h.getHealth() + getAmount()); }

	void update(Hero& h) override
	{
		if (this->getPos().x == h.getPos().x && this->getPos().y == h.getPos().y)
			this->cure(h);
	}
};