#pragma once
#include "ludoBoard.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
//ALL classes,varaibles and functions Named with camelCase convention
int main() {
    srand(time(0));
    Board boardObj;

    boardObj.initPieces();
    boardObj.initBoard();
    boardObj.draw();
    
    cout << "\n\tPress Enter to exit...";
    cout << "\n\tPress R to Roll...";
    char ch = 'W';
    while (ch != '\n')
    {
        ch = cin.get();
        cin.ignore(100,'\n');
        boardObj.draw();
        if (ch == 'r' || 'R')
            boardObj.diceRoll();
    }
    

    return 0;
}