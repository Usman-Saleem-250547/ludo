#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
class Goti {
private:
	int teamNo;
	char color;		//Color of the team
	int og_x;		//When defeated returns to this X position
	int og_y;		//When defeated returns to this Y position 
	int x;
	int y;
	int id;
	bool alive;		//When defeated or not spawned this turns to 0
public:
	Goti() {

	}
	Goti(char col, int teamNo,int Y,int X) {
		color = col;
		this->teamNo = teamNo;
		og_x = X;
		x = X;
		og_y = Y;
		y = Y;
		alive = 0;
	}
	int getTeamNo() const {
		return teamNo;
	}
	int& getX() {
		// gesetter
		return x;
	}
	int& getY() {
		// gesetter
		return y;
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
			x = og_x;
			y = og_y;
		}
		// else;
	}
};