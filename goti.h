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
protected:
	int teamNo;
	char color;		//Color of the team
	int og_r;		//When defeated returns to this Row position
	int og_c;		//When defeated returns to this Column position
	int start_r; 	// start_ tells where the gotis will spawn/start from when got a 0
	int start_c;
	int row;
	int col;
	int id;
	bool alive;		//When defeated or not spawned this turns to 0
// protected:
public:   
	static Goti ***gotis; //aggregation relationship with board, rn no use but i think it will come handy
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
		// start_ tells where the gotis will spawn/start from when got a 0
		if (color == 'G') {
			start_c = 2;
			start_r = 6;
		}
		if (color == 'Y') {
			start_c = 8;
			start_r = 2;
		}
		if (color == 'R') {
			start_c = 12;
			start_r = 8;
		}
		if (color == 'B') {
			start_c = 6;
			start_r = 12;
		}
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
	//Movement Logic
	void operator ++ (){

		if ((row == 6)&& ((col >= 0 && col < 5) || (col >= 9 && col < 14))) {
			++col;
		}
		else if (row==6&&col == 5) {
			row = 5;
			col = 6;
		}
		else if (row == 5 && col == 8) {
			row = 6;
			col = 9;
		}
		else if ((col == 14) && (row>=6 && row<8)) {
			row++;
		}
		else if ((col == 0) && (row > 6 && row <= 8)) {
			row--;
		}
		else if ((row == 8) && ((col > 0 && col <= 5) || (col > 9 && col <= 14))) {
			--col;
		}
		else if (col == 9 && row == 8) {
			row = 9;
			col = 8;
		}
		else if ((row == 0) && (col >= 6 && col < 8)) {
			++col;
		}
		else if ((col == 8)&&((row>=0&&row<5)||(row>=9&&row<14))) {
			++row;
		}
		else if ((row == 14)&& ((col > 6 && col <= 8))) {
				--col;	
		}
		else if((col==6)&&((row<=14&&row>9)||(row > 0 && row <= 5))){
			--row;
		}
		else if (col == 6 && row == 9) {
			row = 8;
			col = 5;
		}
		
		
		
	}
	bool spawnGoti() {
		if (alive) {
			return false;
		}
		alive = 1;
		col = start_c;
		row = start_r;
		return true;
	}
	void returnHome() {
		col = og_c;
		row = og_r;
		alive = 0;
	}
	void pass() {
		row = 7;
		col = 7;
		alive = 0; // if user wants, he can recall his passed goti later to play again. It's not a bug, it's a feature.
	}
	bool getState() {
		return alive;
	}
	bool operator==(const Goti& obj) {
		if (row == obj.row && col == obj.col) return true;
		else return false;
	}
	std::ostream& operator<<(const Goti& obj) {
		int rem = 0, index; // remaining, index from 0 - 3 to determine which color goti belonged to
		char player_color = obj.getColor();
		if (player_color == 'G') index = GREEN_INDEX;
		else if (player_color == 'B') index = BLUE_INDEX;
		else if (player_color == 'R') index = RED_INDEX;
		else if (player_color == 'Y') index = YELLOW_INDEX;
		for (int i = 0; i < 4; i++) {
			if (gotis[index][i]->getState()) rem++;
		}
		std::cout << "Color: " << color << "\nRemaining Pieces: " << rem << "\n";
		return std::cout;
	}
};

Goti*** Goti::gotis = new Goti **[4];