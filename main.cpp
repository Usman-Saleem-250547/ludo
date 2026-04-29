#include "ludoBoard.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
//ALL classes,varaibles and functions Named with camelCase convention
int main() {
    board boardObj;

    boardObj.initBoard();
    boardObj.initPieces();

    boardObj.draw();

    cout << "\n\tPress Enter to exit...";
    cout << "\n\tPress R to Roll...";
    cin.get();

    return 0;
}