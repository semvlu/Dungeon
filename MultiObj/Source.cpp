#include "main.h"
#include "Hero.h"
#include "Creature.h"

Hero	 gHero(2, 2);

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 10;
const int GHEIGHT = 10;
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

vector <Creature> C;
Creature gCreature;
Devil Dev(7, 3, 'D');
Witch Granny(5, 8, 'G');

vector <Item> Iobj;
Trigger gTrigger(5, 5, 10);
Trigger gTrigger1;
Trap trap1(4, 1, 3, 't');
Med med1(7, 7, 7, 'M');

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

int main(int argc, char** argv)
{
	srand(time(NULL));
	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[6];

	// Setup a clear dungeon
	setupBoard();

	C.push_back(gCreature);
	C.push_back(Dev);
	C.push_back(Granny);
	C[0].setPos(5, 6);
	C[1].setPos(7, 3);
	C[2].setPos(3, 8);

	Iobj.push_back(gTrigger);
	Iobj.push_back(gTrigger1);
	Iobj.push_back(trap1);
	Iobj.push_back(med1);

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
	try
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
			string inv = "Invalid input";
			throw inv;
			break;
		}
	}
	catch (string i) { cout << i << endl; }
}

//******************************************************************
//
// * �P�_��m�O�_����
//==================================================================
bool isPositionValid(Position& pos)
//==================================================================
{
	// Check whether it is an empty space
	try
	{
		if (gBoard[pos.y][pos.x] == GNOTHING)
			return true;
		else
		{
			string inv = "Invalid location";
			throw inv;
		}
	}
	catch (string i)
	{
		cout << i << endl;
		return false;
	}
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimum, float maximum)
//==================================================================
{
	return std::max(minimum, std::min(n, maximum));
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
			if (i == 0 || i == GHEIGHT - 1) 
				gBoard[i][j] = GWALL;
			else if (j == 0 || j == GWIDTH - 1) 
				gBoard[i][j] = GWALL;
			else 
				gBoard[i][j] = GNOTHING;
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
		for (int j = 0; j < GWIDTH; j++)
			drawBoard[i][j] = gBoard[i][j];
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	vector <Position> c;
	for (int i = 0; i < C.size(); i++)
	{
		c.push_back(C[i].getPos());
		drawBoard[c[i].y][c[i].x] = C[i].getIcon();
	}

	vector <Position> i_obj;
	for (int i = 0; i < Iobj.size(); i++)
	{
		i_obj.push_back(Iobj[i].getPos());
		drawBoard[i_obj[i].y][i_obj[i].x] = Iobj[i].getIcon();
	}

	for (int i = 0; i < C.size(); i++)
	{
		if (h.x == c[i].x && h.y == c[i].y)
			gHero.damage(1);
	}
	
	/************************************************************************/

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
	std::cout << "The hero is level " << gHero.getLevel() << "\n";
	std::cout << "has " << gHero.getExp() << " EXP" << "\n";
	std::cout << "need " << gHero.getMaxExp() - gHero.getExp() << " to level up\n";
	std::cout << "Heo has " << gHero.getHealth() << " health\n";
	std::cout << "Use arrow key to move Hero @\n";
	std::cout << "Use Every time you step on a trigger T. the hero gets " << Iobj[0].getAmount() << " or " << Iobj[1].getAmount() << " EXP points\n";
	std::cout << "Press ESC key to exit\n";
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
	/*else
		std::cout << "invalid input\n";*/

	for (int i = 0; i < C.size(); i++)
		C[i].update(gHero.getPos());

	for (int i = 0; i < Iobj.size(); i++)
		Iobj[i].update(gHero);
	draw();
	drawInfo();
}
