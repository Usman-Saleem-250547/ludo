#pragma once
// #include "ludoBoard.h"
#include "team.h"
#include "classic.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
//ALL classes,varaibles and functions Named with camelCase convention
int main() {
    srand(time(0));
    Board *ludoGame = new Classic();

    ludoGame->startGame();
    delete ludoGame;
    delete [] Goti::gotis;
    return 0;
}