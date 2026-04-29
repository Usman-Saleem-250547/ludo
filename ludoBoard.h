#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "goti.h"
using namespace std;
class Board {
private:
    const int BLACK = 0;
    const int BLUE = 1;
    const int GREEN = 2;
    const int RED = 4;
    const int YELLOW = 14;
    const int WHITE = 7;
    const int GRAY = 8;
    const int BRIGHT_WHITE = 15;
    


    string label[15][15];   //Main Board
    int bg[15][15];         //background colors
    int fg[15][15];         //font colors



    int gx[4][4], gy[4][4];      // goti positions
    char gsym[4][4];             // goti symbols
    int gcolor[4][4];            // goti colors
    int gid[4][4];               // goti ids
    HANDLE hConsole;             //ts Way Above Our Paygrade DO NOT TOUCH USMAN

    //Gotis
    Goti** greenGotis, yellowGotis, redGotis, blueGotis;
public:

    Board() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);     //Console Stuff DO NOT MODIFY
        // green
        greenGotis = new Goti*[4];
        greenGotis[0] = new Goti('G',1,1,1);
        greenGotis[1] = new Goti('G',1,1,4);
        greenGotis[2] = new Goti('G',1,4,1);
        greenGotis[3] = new Goti('G',1,4,4);

        // yellow 
        yellowGotis = new Goti*[4];
        yellowGotis[0] = new Goti('Y', 2, 1, 10);
        yellowGotis[1] = new Goti('Y', 2, 1, 13);
        yellowGotis[2] = new Goti('Y', 2, 4, 10);
        yellowGotis[3] = new Goti('Y', 2, 4, 13);

        // red
        redGotis = new Goti*[4];
        redGotis[0] = new Goti('R', 3, 10, 10);
        redGotis[1] = new Goti('R', 3, 10, 13);
        redGotis[2] = new Goti('R', 3, 13, 10);
        redGotis[3] = new Goti('R', 3, 13, 13);

        // blue
        blueGotis = new Goti*[4];
        blueGotis[0] = new Goti('B', 4, 10, 1);
        blueGotis[1] = new Goti('B', 4, 10, 4);
        blueGotis[2] = new Goti('B', 4, 13, 1);
        blueGotis[3] = new Goti('B', 4, 13, 4);
    }
    ~Board() {
        for (int i = 0; i < 4; i++) {
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
    void setColor(int fgColor, int bgColor) {           //Sets Color set by using the Console Thing Above :P
        SetConsoleTextAttribute(hConsole, (bgColor * 16) + fgColor);
    }


    /*void initBoard() {          
        
        //Board Initializer
        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 15; x++) {
                label[y][x] = "   ";
                bg[y][x] = BLACK;
                fg[y][x] = GRAY;
            }
        }


        // GREEN +YELLOW BASE
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 6; x++) bg[y][x] = GREEN;   //This fills that part of the Array with a Green Box
            for (int x = 9; x < 15;x++) bg[y][x] = YELLOW; //The colors are given as int values above
        }

        // RED + BLUE BASE
        for (int y = 9; y < 15; y++) {
            for (int x = 9; x < 15; x++) bg[y][x] = RED;
            for (int x = 0; x < 6; x++) bg[y][x] = BLUE;
        }

        // PATHS
        for (int i = 1; i < 6; i++) {
            bg[i][7] = GREEN;
            bg[14 - i][7] = RED;
            bg[7][i] = BLUE;
            bg[7][14 - i] = YELLOW;
        }

        // CENTER
        for (int y = 6; y <= 8; y++)
            for (int x = 6; x <= 8; x++)
                label[y][x] = " H ";

        // SAFE ZONES
        label[6][2] = " @ ";
        label[2][8] = " @ ";
        label[8][12] = " @ ";
        label[12][6] = " @ ";
    }
*/
    
    void initPieces() {
        //This initializes the pieces IDs so they can be printed like G1 or G2, here 1 and 2 are the ID
        for (int i = 0; i < 4; i++) {
            blueGotis[i]->getID() = i+1;
            redGotis[i]->getID() = i+1;
            greenGotis[i]->getID() = i+1;
            yellowGotis[i]->getID() = i+1;
        }
        /*pr is an array to store y positions
        pc is an array to store x positions
        psym store the char to print like in G1, G is the color
        pid stores the ID
        I have combined them into a single class Goti but proper implementation in draw() is needed*/
        for (int i = 0; i < 4; i++) {
            gy[0][i] = greenGotis[i]->getY(); gx[0][i] = greenGotis[i]->getX();
            gsym[0][i] = greenGotis[0]->getColor(); gcolor[0][i] = BRIGHT_WHITE; gid[0][i] = greenGotis[i]->getID();

            gy[1][i] = yellowGotis[i]->getY(); gx[1][i] = yellowGotis[i]->getX();
            gsym[1][i] = yellowGotis[0]->getColor(); gcolor[1][i] = WHITE; gid[1][i] = yellowGotis[i]->getID();

            gy[2][i] = redGotis[i]->getY(); gx[2][i] = redGotis[i]->getX();
            gsym[2][i] = redGotis[0]->getColor(); gcolor[2][i] = BRIGHT_WHITE; gid[2][i] = redGotis[i]->getID();

            gy[3][i] = blueGotis[i]->getY(); gx[3][i] = blueGotis[i]->getX();
            gsym[3][i] = blueGotis[0]->getColor(); gcolor[3][i] = BRIGHT_WHITE; gid[3][i] = blueGotis[i]->getID();
        }
    }

    //DICE ROLL
    

    // DRAW BOARD

    void draw() {

        system("cls");

        cout << "\n\t \t\t\t   ==== LUDO STAR ====\t\n\n";

        // looping through the board, and if gotis are there, then print them else print from default board
        for (int y = 0; y < 15; y++) {
            cout << "\t      ";

            for (int x = 0; x < 15; x++) {

                int found = 0;
                char sym = ' ';
                int col = WHITE;
                int id = 0;

                // looping through team/color
                for (int p = 0; p < 4; p++) {
                    // then looping through each goti of respective color
                    for (int i = 0; i < 4; i++) {
                        if (gy[p][i] == y && gx[p][i] == x) {
                            found = 1;
                            sym = gsym[p][i];
                            col = gcolor[p][i];
                            id = gid[p][i];
                        }
                    }
                }

                if (found) {
                    setColor(col, bg[y][x]);
                    cout << sym << id << " ";
                } else {
                    setColor(fg[y][x], bg[y][x]);
                    cout << label[y][x];
                }

                setColor(WHITE, BLACK);
                cout << "|";
            }
            cout << "\n";
        }
    }

};


