#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <string>		// for fullWidth board display
#include <ctime>		// for time loop function
#include "Position.h"
#include "Hero.h"
#include "Creature.h"
#include "Trigger.h"

// �Ψ��x�s�������
std::string gBoard[GHEIGHT][GWIDTH] = {
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL
};

Hero	 gHero(2, 2);
Creature gCreature(4, 4);
Trigger  gTrigger(5, 5, 10);

int main(int argc, char** argv)
{
	// Initialize board
	initBoard();

	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[6];

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
