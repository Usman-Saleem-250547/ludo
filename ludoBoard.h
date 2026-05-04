#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "goti.h"
#include <ctime>
#include <cstdlib>
using namespace std;

class Board
{
private:
    const int BLACK = 0;
    const int BLUE = 1;
    const int GREEN = 2;
    const int RED = 4;
    const int YELLOW = 14;
    const int WHITE = 7;
    const int GRAY = 8;
    const int BRIGHT_WHITE = 15;

    // in these 15 x 15 arrays, the first are rows (y) and the second are columnx (x)
    // these are the background of board and represent the colors of the cell and if the cell is special e.g. safe
    string label[15][15]; // Main Board
    int bg[15][15];       // background colors
    int fg[15][15];       // font colors

    // there are four teams and each team has 4 gotis, so 4 x 4 arrays
    int gr[4][4], gc[4][4]; // goti positions, rows and cols
    char gsym[4][4];        // goti symbols
    int gcolor[4][4];       // goti colors
    int gid[4][4];          // goti ids
    HANDLE hConsole;        // ts Way Above Our Paygrade DO NOT TOUCH USMAN

    // Gotis
    Goti **greenGotis, **yellowGotis, **redGotis, **blueGotis;

protected:
    int choice; // to store the choice of goti to move, 0 - 3
    int turn;   // from 0 - 3, tells which team's turn it is according to the index given in macros
    int roll;   // stores the value of dice roll, 0 - 5
public:
    Board();
    ~Board();
    void setColor(int fgColor, int bgColor)
    { // Sets Color set by using the Console Thing Above :P
        SetConsoleTextAttribute(hConsole, (bgColor * 16) + fgColor);
    }
    void initBoard();
    void initPieces();
    // dice rolling functions
    void turnChecker();
    void diceRoll();
    void checkRoll();
    void draw();
    void gotaSix();
    void moveGoti();
    virtual void verifyKill() = 0;
    void startGame()
    {
        turnChecker();
    }; // star the game after board is initalized and drawn
    virtual bool isFinished() = 0;
};
Board::Board()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Console Stuff DO NOT MODIFY

    // green
    greenGotis = new Goti *[4];
    greenGotis[0] = new Goti('G', 1, 1, 1);
    greenGotis[1] = new Goti('G', 1, 1, 4);
    greenGotis[2] = new Goti('G', 1, 4, 1);
    greenGotis[3] = new Goti('G', 1, 4, 4);

    // yellow
    yellowGotis = new Goti *[4];
    yellowGotis[0] = new Goti('Y', 2, 1, 10);
    yellowGotis[1] = new Goti('Y', 2, 1, 13);
    yellowGotis[2] = new Goti('Y', 2, 4, 10);
    yellowGotis[3] = new Goti('Y', 2, 4, 13);

    // red
    redGotis = new Goti *[4];
    redGotis[0] = new Goti('R', 3, 10, 10);
    redGotis[1] = new Goti('R', 3, 10, 13);
    redGotis[2] = new Goti('R', 3, 13, 10);
    redGotis[3] = new Goti('R', 3, 13, 13);

    // blue
    blueGotis = new Goti *[4];
    blueGotis[0] = new Goti('B', 4, 10, 1);
    blueGotis[1] = new Goti('B', 4, 10, 4);
    blueGotis[2] = new Goti('B', 4, 13, 1);
    blueGotis[3] = new Goti('B', 4, 13, 4);

    Goti::gotis[GREEN_INDEX] = greenGotis;
    Goti::gotis[YELLOW_INDEX] = yellowGotis;
    Goti::gotis[RED_INDEX] = redGotis;
    Goti::gotis[BLUE_INDEX] = blueGotis;

    // testing for win for classic
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         Goti::gotis[i][j]->spawnGoti();
    //         if (i == 0 && j == 0) continue;
    //             Goti::gotis[i][j]->pass();
    //     }
    // }
    // go to line 279

    // testing for win for team
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         Goti::gotis[i][j]->spawnGoti();
    //         if (j == 3) continue;
    //             Goti::gotis[i][j]->pass();
    //     }
    // }
}
Board::~Board()
{
    for (int i = 0; i < 4; i++)
    {
        delete greenGotis[i];
        delete yellowGotis[i];
        delete redGotis[i];
        delete blueGotis[i];
    }
    delete[] greenGotis;
    delete[] yellowGotis;
    delete[] redGotis;
    delete[] blueGotis;
}
void Board::initBoard()
{
    // Board Initializer
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            label[y][x] = "   ";
            bg[y][x] = BLACK;
            fg[y][x] = GRAY;
        }
    }

    // GREEN +YELLOW BASE
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
            bg[y][x] = GREEN; // This fills that part of the Array with a Green Box
        for (int x = 9; x < 15; x++)
            bg[y][x] = YELLOW; // The colors are given as int values above
    }

    // RED + BLUE BASE
    for (int y = 9; y < 15; y++)
    {
        for (int x = 9; x < 15; x++)
            bg[y][x] = RED;
        for (int x = 0; x < 6; x++)
            bg[y][x] = BLUE;
    }

    // central paths, where goti go at the end
    for (int i = 1; i < 6; i++)
    {
        bg[i][7] = YELLOW;
        bg[14 - i][7] = BLUE;
        bg[7][i] = GREEN;
        bg[7][14 - i] = RED;
    }

    //  CENTER
    for (int y = 6; y <= 8; y++)
        for (int x = 6; x <= 8; x++)
            label[y][x] = " H ";

    //  SAFE ZONES, the starting place of goti when they get 6. they can't get killed here
    label[6][2] = " @ ";
    label[2][8] = " @ ";
    label[8][12] = " @ ";
    label[12][6] = " @ ";
}
void Board::initPieces()
{
    // This initializes the pieces IDs so they can be printed like G1 or G2, here 1 and 2 are the ID
    for (int i = 0; i < 4; i++)
    {
        greenGotis[i]->getID() = i + 1;
        yellowGotis[i]->getID() = i + 1;
        redGotis[i]->getID() = i + 1;
        blueGotis[i]->getID() = i + 1;
    }
    /*pr is an array to store row positions
    pc is an array to store column positions
    psym store the char to print like in G1, G is the color
    pid stores the ID
    I have combined them into a single class Goti but proper implementation in draw() is needed*/
    for (int i = 0; i < 4; i++)
    {
        gc[GREEN_INDEX][i] = greenGotis[i]->getCol();
        gr[GREEN_INDEX][i] = greenGotis[i]->getRow();
        gsym[GREEN_INDEX][i] = greenGotis[i]->getColor();
        gcolor[GREEN_INDEX][i] = BRIGHT_WHITE;
        gid[GREEN_INDEX][i] = greenGotis[i]->getID();

        gc[YELLOW_INDEX][i] = yellowGotis[i]->getCol();
        gr[YELLOW_INDEX][i] = yellowGotis[i]->getRow();
        gsym[YELLOW_INDEX][i] = yellowGotis[i]->getColor();
        gcolor[YELLOW_INDEX][i] = WHITE;
        gid[YELLOW_INDEX][i] = yellowGotis[i]->getID();

        gc[RED_INDEX][i] = redGotis[i]->getCol();
        gr[RED_INDEX][i] = redGotis[i]->getRow();
        gsym[RED_INDEX][i] = redGotis[i]->getColor();
        gcolor[RED_INDEX][i] = BRIGHT_WHITE;
        gid[RED_INDEX][i] = redGotis[i]->getID();

        gc[BLUE_INDEX][i] = blueGotis[i]->getCol();
        gr[BLUE_INDEX][i] = blueGotis[i]->getRow();
        gsym[BLUE_INDEX][i] = blueGotis[i]->getColor();
        gcolor[BLUE_INDEX][i] = BRIGHT_WHITE;
        gid[BLUE_INDEX][i] = blueGotis[i]->getID();
    }
}
void Board::turnChecker()
{
    if (turn == GREEN_INDEX)
    {
        cout << "Green's Turn\n";
    }
    else if (turn == YELLOW_INDEX)
    {
        cout << "Yellow's Turn\n";
    }
    else if (turn == RED_INDEX)
    {
        cout << "Red's Turn\n";
    }
    else if (turn == BLUE_INDEX)
    {
        cout << "Blue's Turn\n";
    }
    diceRoll(); // the player with dice the roll
}
void Board::diceRoll()
{
    roll = (rand() % 6) + 1;
    cout << "You Rolled a " << roll << "\n";
    checkRoll(); // after dicing, the program will check the roll
}
void Board::checkRoll()
{
    if (roll == 6)
    {
        cout << "Choose a Goti to Play or Add a New Goti from Home: " << endl;
    }
    else
    {
        cout << "Choose a Goti to Play: " << endl;
    }
    cout << "1. " << gsym[turn][0] << gid[turn][0] << endl;
    cout << "2. " << gsym[turn][1] << gid[turn][1] << endl;
    cout << "3. " << gsym[turn][2] << gid[turn][2] << endl;
    cout << "4. " << gsym[turn][3] << gid[turn][3] << endl;
    cin >> choice;
    if (choice <= 0)
        choice = 1; // input validation
    choice = (choice - 1) % 4;
    cout << "You Chosed " << gsym[turn][choice] << gid[turn][choice] << " to move." << endl;
    if (roll == 6)
        gotaSix();
    else
        moveGoti();
    // Goti::gotis[0][0]->pass(); //testing for classic win
    // Goti::gotis[0][3]->pass(); //testing for team win
    initPieces();          // to get updated gc and gr
    draw();                // redraw the board after the move
    // check if game is finished
    if (isFinished()) {
        cout << "\tGame is finished. Thanks for being with us :P\n";
        string temp;
        getline(cin, temp);
        return;
    }
    turn = (turn + 1) % 4; // next team's turn

    turnChecker(); // check the next turn
}
void Board::draw()
{
    system("cls");

    cout << "\n\t \t\t\t   ==== LUDO STAR ====\t\n\n";

    // looping through the board, and if gotis are there, then print them else print from default board
    // the y and x in this loop don't represent the row and column of the board, they are just for looping through the 2D array
    for (int r = 0; r < 15; r++)
    {
        cout << "\t      ";

        for (int c = 0; c < 15; c++)
        {

            int found = 0;
            char sym = ' ';
            int col = WHITE;
            int id = 0;

            // looping through team/color
            for (int p = 0; p < 4; p++)
            {
                // then looping through each goti of respective color
                for (int i = 0; i < 4; i++)
                {
                    if (gc[p][i] == c && gr[p][i] == r)
                    {
                        found = 1;
                        sym = gsym[p][i];
                        col = gcolor[p][i];
                        id = gid[p][i];
                    }
                }
            }

            if (found)
            {
                setColor(col, bg[r][c]);
                cout << sym << id << " ";
            }
            else
            {
                setColor(fg[r][c], bg[r][c]);
                cout << label[r][c];
            }

            setColor(WHITE, BLACK);
            cout << "|";
        }
        cout << "\n";
    }
}
void Board::gotaSix()
{ // When the player gets a six it checks if the Goti is alive
    if (Goti::gotis[turn][choice]->spawnGoti())
    { // If it is alive it spawns the Goti, else it moves it
    }
    else
    {
        moveGoti();
    }
}

void Board::moveGoti()
{
    int takeTurn;
    if (Goti::gotis[turn][choice]->getState())
    {
        for (int i = 0; i < roll; i++)
            ++(*Goti::gotis[turn][choice]);
    }
    else
    {
        draw();
        cout << "Cannot Move the Selected Goti, Choose Another one by Pressing 1 or Press 0 to Skip this Turn" << endl;
        cin >> takeTurn; // if takeTurn=0 turn is skipped
        if (takeTurn == 1)
            checkRoll();
    }
    verifyKill(); // after moving the goti, check if it killed any opponent goti
}