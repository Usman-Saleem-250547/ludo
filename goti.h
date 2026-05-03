#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

#define GREEN_INDEX 0
#define YELLOW_INDEX 1
#define RED_INDEX 2
#define BLUE_INDEX 3
class Goti
{
protected:
	int teamNo;
	char color;	 // Color of the team
	int og_r;	 // When defeated returns to this Row position
	int og_c;	 // When defeated returns to this Column position
	int start_r; // start_ tells where the gotis will spawn/start from when got a 0
	int start_c;
	int row;
	int col;
	int id;
	bool alive; // When defeated or not spawned this turns to 0
	bool passed;
public:
	static Goti ***gotis; // aggregation relationship with board, rn no use but i think it will come handy
	Goti() {}
	~Goti() { delete[] gotis; }
	Goti(char color, int teamNo, int row, int col);
	// gesetters
	int &getRow() { return row; }
	int &getCol() { return col; }
	int &getID() { return id; }

	char getColor() const { return color; } 
	void checkAlive();
	Goti &operator++();
	bool spawnGoti();
	void returnHome();
	void pass();
	bool getState();
	bool isSafe();
	bool operator==(const Goti &);
	std::ostream &operator<<(const Goti &);
	static string Goti::getColorName(unsigned int);
};

Goti ***Goti::gotis = new Goti **[4];

Goti::Goti(char color, int teamNo, int row, int col) : passed(0)
{
	this->color = color;
	this->teamNo = teamNo;
	og_r = row;
	this->row = row;
	og_c = col;
	this->col = col;
	alive = 0;
	// start_ tells where the gotis will spawn/start from when got a 0
	if (color == 'G')
	{
		start_c = 2;
		start_r = 6;
	}
	if (color == 'Y')
	{
		start_c = 8;
		start_r = 2;
	}
	if (color == 'R')
	{
		start_c = 12;
		start_r = 8;
	}
	if (color == 'B')
	{
		start_c = 6;
		start_r = 12;
	}
}
void Goti::checkAlive()
{
	if (alive == 0)
	{
		row = og_r;
		col = og_c;
	}
}
Goti &Goti::operator++()
{
	if (passed)
		return *this;
	// special cases of they have completed their rotation
	if (color == 'G' && row == 7 && col < 6)
	{
		col++;
		if (col == 6)
			pass();
	}
	else if (color == 'R' && row == 7 && col > 8)
	{
		col--;
		if (col == 8)
			pass();
	}
	else if (color == 'Y' && row < 6 && col == 7)
	{
		row++;
		if (row == 6)
			pass();
	}
	else if (color == 'B' && row > 8 && col == 7)
	{
		row--;
		if (row == 8)
			pass();
	}
	// movement for goti's through out the board
	if ((row == 6) && ((col >= 0 && col < 5) || (col >= 9 && col < 14)))
	{
		++col;
	}
	else if (row == 6 && col == 5)
	{
		row = 5;
		col = 6;
	}
	else if (row == 5 && col == 8)
	{
		row = 6;
		col = 9;
	}
	else if ((col == 14) && (row >= 6 && row < 8))
	{
		row++;
	}
	else if ((col == 0) && (row > 6 && row <= 8))
	{
		row--;
	}
	else if ((row == 8) && ((col > 0 && col <= 5) || (col > 9 && col <= 14)))
	{
		--col;
	}
	else if (col == 9 && row == 8)
	{
		row = 9;
		col = 8;
	}
	else if ((row == 0) && (col >= 6 && col < 8))
	{
		++col;
	}
	else if ((col == 8) && ((row >= 0 && row < 5) || (row >= 9 && row < 14)))
	{
		++row;
	}
	else if ((row == 14) && ((col > 6 && col <= 8)))
	{
		--col;
	}
	else if ((col == 6) && ((row <= 14 && row > 9) || (row > 0 && row <= 5)))
	{
		--row;
	}
	else if (col == 6 && row == 9)
	{
		row = 8;
		col = 5;
	}
	return *this;
}
bool Goti::spawnGoti()
{
	if (passed || alive)
		return false;
	alive = 1;
	col = start_c;
	row = start_r;
	return true;
}
void Goti::returnHome()
{
	col = og_c;
	row = og_r;
	alive = 0;
}
void Goti::pass()
{
	row = 7;
	col = 7;
	passed = 1;
}
bool Goti::getState()
{
	if (passed)
		return false; // can't move the passed goti
	return alive;
}
bool Goti::isSafe()
{
	if (row == 6 && col == 2)
		return true;
	if (row == 2 && col == 8)
		return true;
	if (row == 8 && col == 12)
		return true;
	if (row == 12 && col == 6)
		return true;
	return false;
}
bool Goti::operator==(const Goti &obj)
{
	if (row == obj.row && col == obj.col)
		return true;
	else
		return false;
}
std::ostream &Goti::operator<<(const Goti &obj)
{
	int rem = 0, index; // remaining, index from 0 - 3 to determine which color goti belonged to
	char player_color = obj.getColor();
	if (player_color == 'G')
		index = GREEN_INDEX;
	else if (player_color == 'B')
		index = BLUE_INDEX;
	else if (player_color == 'R')
		index = RED_INDEX;
	else if (player_color == 'Y')
		index = YELLOW_INDEX;
	for (int i = 0; i < 4; i++)
	{
		if (gotis[index][i]->passed)
			rem++;
	}
	std::cout << "Color: " << color << "\nRemaining Pieces: " << rem << "\n";
	return std::cout;
}
string Goti::getColorName(unsigned int index)
{
	index = index % 4;
	if (index == GREEN_INDEX)
		return "GREEN";
	if (index == BLUE_INDEX)
		return "BLUE";
	if (index == RED_INDEX)
		return "RED";
	if (index == YELLOW_INDEX)
		return "YELLOW";
}