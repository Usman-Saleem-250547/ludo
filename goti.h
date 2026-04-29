#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
class Goti {
private:
	int teamNo;
	char color;
	int og_x;		//When defeated returns to this X position
	int og_y;		//When defeated returns to this Y position 
	int x;
	int y;
	int id;
	bool alive;		//When defeated or not spawned this turns to 0
public:
	Goti(char col, int No,int Y,int X) {
		color = col;
		teamNo = No;
		og_x = X;
		x = X;
		og_y = Y;
		y = Y;
		alive = 0;
	}
	int getteamNo() const {
		return teamNo;
	}
	int getx() const {
		return x;
	}
	int gety() const {
		return y;
	}
	void setx(int newX) {
		x = newX;
	}
	char getColor() const{
		return color;
	}
	void sety(int newY) {
		y = newY;
	}
	void checkAlive() {
		if (alive == 0) {
			x = og_x;
			y = og_y;
		}
		else;
	}
	int getID() const {
		return id;
	}
	void setID(int ID) {
		id = ID;
	}
};