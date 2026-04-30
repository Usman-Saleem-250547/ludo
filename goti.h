#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define GREEN_INDEX 0
#define YELLOW_INDEX 1
#define RED_INDEX 2
#define BLUE_INDEX 3
class Goti {
private:
	int teamNo;
	char color;		//Color of the team
	int og_r;		//When defeated returns to this Row position
	int og_c;		//When defeated returns to this Column position 
	int row;
	int col;
	int id;
	bool alive;		//When defeated or not spawned this turns to 0
	static Goti ***gotis = new Goti**[4];   //aggregation relationship with board, rn no use but i think it will come handy
public:
	Goti() {

	}
	~Goti() {
		delete [] gotis;
	}
	Goti(char color, int teamNo,int col,int row) {
		this->color = color;
		this->teamNo = teamNo;
		og_r = row;
		this->row = row;
		og_c = col;
		this->col = col;
		alive = 0;
	}
	int getTeamNo() const {
		return teamNo;
	}
	int& getRow() {
		// gesetter
		return col;
	}
	int& getCol() {
		// gesetter
		return row;
	}
	int& getID() {
		// gesetter
		return id;
	}
	char getColor() const{
		return color;
	}
	void checkAlive() {
		if (alive == 0) {
			row = og_r;
			col = og_c;
		}
		// else;
	}
	void kill() {
		alive = 0;
	}
	void spawn(int row, int col) {
		alive = 1;
		this->row = row;
		this->col = col;
	}
};