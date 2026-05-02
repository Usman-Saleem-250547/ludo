#include "ludoBoard.h"

class Classic: protected Board {
public:
    Classic() {
        initPieces();
        initBoard();
        draw();
    }
    // void verifyKill() override {
    //     // through each color
    //     for (int i = 0; i < 4; i++) {
    //         // through each goti of the color
    //         for (int j = 0; j < 4; j++) {
    //             // check if both position equal
    //             if (turn == i) continue; // so that the goti don't suicide, lorem dolor ipsum
    //             if (Goti::gotis[turn][choice] == Goti::gotis[i][j]) {
    //                 Goti::gotis[i][j]->returnHome();
    //                 // if any team has >1 of it's gotis at the same place, it will kill them both.
    //                 // it's a feature :p
    //             }
    //         }
    //     }
    // }
    void startGame() {
        turnChecker();
    }; // star the game after board is initalized and drawn
};