#include "ludoBoard.h"

class Team: public Board {
private:
    int teams[2][2] = {{BLUE_INDEX, RED_INDEX}, {YELLOW_INDEX, GREEN_INDEX}}; // 2 teams of 2 player, generic
    int team_turn;
public:
    Team():team_turn(0) {
        initPieces();
        initBoard();
        draw();
        string temp;
        cout << "Before proceeding, this game is team based meaning a team membor can't kill his fellow membor's goti.\nFollowing are the teams: \n\t1) " << Goti::getColorName(teams[0][0]) << " and " << Goti::getColorName(teams[0][1]) << "\n\t2) " << Goti::getColorName(teams[1][0]) << " and " << Goti::getColorName(teams[1][1]) << "\nEnter any key to continue: ";
        cin.ignore();
        getline(cin, temp);
    }
    void verifyKill() override {
        // through each color
        for (int i = 0; i < 4; i++) {
            // checking which team, player belong to
            for (int k = 0; k < 2; k++) {
                for (int m = 0; m < 2; m++) {
                    if (turn == teams[k][m]) {
                        team_turn = k;
                    }
                }
            }
            // the current player can't kill himself and his fellow membor
            if (i == teams[team_turn][0] || i == teams[team_turn][1]) continue;
            
            // through each goti of the color
            for (int j = 0; j < 4; j++) {
                // check if both position equal
                if (*Goti::gotis[turn][choice] == *Goti::gotis[i][j]) {
                    // if in safe location
                    if (Goti::gotis[i][j]->isSafe()) continue;
                    Goti::gotis[i][j]->returnHome();
                    // if any team has >1 of it's gotis at the same place, it will kill them both.
                    // it's a feature :p
                }
            }
        }
    }
    void startGame() {
        turnChecker();
    }; // star the game after board is initalized and drawn
};