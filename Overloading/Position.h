#pragma once
//************************************************************
// The location in the board
//************************************************************

// Transfer Position change to overloading functions here
/*Please implement your code here*/
struct Position 
{
	int x; // X, y Coordinate
	int y;

	Position operator+(int a)
	{
		y += a;
		return *this;
	}
	Position operator-(int a)
	{
		y -= a;
		return *this;
	}
	Position operator*(int a)
	{
		x -= a;
		return *this;
	}
	Position operator/(int a)
	{
		x += a;
		return *this;
	}
};

/************************************************************************/
