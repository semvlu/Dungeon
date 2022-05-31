#include "main.h"
#include "Hero.h"
#include <fstream>
#include <sstream>
using namespace std;
Hero	 gHero(2, 2);

class Creature {//creature class 
private:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
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
			this->sIcon = 'C';
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

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 20;
const int GHEIGHT = 15;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// �Ψ��x�s�������
char gBoard[GHEIGHT][GWIDTH] = {
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL
};

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


Creature gCreature;

// function declare
// ������J���A
void keyUpdate(bool key[]);
// �P�_��m�O�_����
bool isPositionValid(Position& loc);
// ��l�ƪ���
void setupBoard();
// ��X����
void draw(void);
// ��X������T
void drawInfo(void);

// �{���D�X�ʨ禡
void update(bool key[]);

Trigger  gTrigger(5, 5, 10);
Trigger  gTrigger1;

int main(int argc, char** argv)
{	
	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[6];

	// Setup a clear dungeon
	setupBoard();
	gCreature.setPos(5, 6);

	// Draw the bord and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Get the press key
	keyUpdate(gKeyState);

	// Run the game loop
	while (!gKeyState[ValidInput::EESC]) {
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}
		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	}
	system("pause");
	return 0;
}

//******************************************************************
//
// * ������J���A
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * �P�_��m�O�_����
//==================================================================
bool isPositionValid(Position& pos)
//==================================================================
{
	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] == GNOTHING) {
		return true;
	}
	return false;
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimun, float maximum)
//==================================================================
{
	return std::max(minimun, std::min(n, maximum));
}

//******************************************************************
//
// * �Q�� call-by-referce �N�p��o�쪺��V�^��
//==================================================================
bool canSee(Position cPos, Position hPos, Position& dir)
//==================================================================
{
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 0;
	do {
		// spot the target position
		if (cPos.x + dir.x * count == hPos.x &&
			cPos.y + dir.y * count == hPos.y) {
			return true;
		}
		count++;
	} while (count < gDistance); // check the range in 4 units
	return false;
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard()
//==================================================================
{
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1) {
				gBoard[i][j] = GWALL;
			}
			else if (j == 0 || j == GWIDTH - 1) {
				gBoard[i][j] = GWALL;
			}
			else {
				gBoard[i][j] = GNOTHING;
			}
		}
	}
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	char drawBoard[GHEIGHT][GWIDTH];

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	Position t = gTrigger.getPos();
	drawBoard[t.y][t.x] = gTrigger.getIcon();

	Position t1 = gTrigger1.getPos();
	drawBoard[t1.y][t1.x] = gTrigger1.getIcon();

	// Hero loses health when steps on creature
	/*Please implement your code here*/
	ofstream f;
	f.open("out.txt");
	f << "Hero icon: " << gHero.getIcon() << ", began at (" << h.x << ", " << h.y << ")" << endl;
	f << "Creature icon: " << gCreature.getIcon() << ", began at (" << c.x << ", " << c.y << ")" << endl;
	f << "Trigger 1 icon: " << gTrigger.getIcon() << ", at (" << t.x << ", " << t.y << ")" << endl;
	f << "Trigger 2 icon: " << gTrigger1.getIcon() << ", at (" << t1.x << ", " << t1.y << ")" << endl;
	f << "Map height: " << GHEIGHT << " , width: " << GWIDTH << endl;
	if (h.x == c.x && h.y == c.y)
	{
		gHero.damage(1);
		f << "Creature deals damage: 1" << endl;
	}

	/************************************************************************/
	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
			f << gBoard[i][j];
		}
		std::cout << "\n";
		f << endl;
	}
	f.close();
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
	ofstream f;
	f.open("out.txt", ios::app);
	std::cout << "The hero is level " << gHero.getLevel() << "\n";
	std::cout << "has " << gHero.getExp() << " EXP" << "\n";
	f << "The Hero has " << gHero.getExp() << " EXP" << "\n";
	std::cout << "need " << gHero.getMaxExp() - gHero.getExp() << " to level up\n";
	std::cout << "Heo has " << gHero.getHealth() << " health\n";
	std::cout << "Use arrow key to moved Hero @\n";
	std::cout << "Use Every time you step on a trigger T. the hero gets " << gTrigger.getExpAmount() << " or " << gTrigger1.getExpAmount() << " EXP points\n";
	std::cout << "Press ESC key to exit\n";
	f.close();
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// �M������
	system("CLS");

	// �O�_��input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		gHero.move(0, -1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		gHero.move(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		gHero.move(-1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		gHero.move(1, 0);
		hasInput = true;
	}
	else {
		std::cout << "invalid input\n";
	}
	gCreature.update(gHero.getPos());
	gTrigger.update(gHero);
	gTrigger1.update(gHero);
	draw();
	drawInfo();
}
