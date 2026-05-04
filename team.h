#include "ludoBoard.h"

class Team : public Board
{
private:
    int teams[2][2] = {{BLUE_INDEX, RED_INDEX}, {YELLOW_INDEX, GREEN_INDEX}}; // 2 teams of 2 player, generic
    int team_turn;

public:
    Team();
    void verifyKill() override;
    bool isFinished() override;
};
Team::Team() : team_turn(0)
{
    initPieces();
    initBoard();
    draw();
    string temp;
    cout << "Before proceeding, this game is team based meaning a team membor can't kill his fellow membor's goti.\nThe game will end when either membor of team has all of his gotis passed.\nFollowing are the teams: \n\t1) " << Goti::getColorName(teams[0][0]) << " and " << Goti::getColorName(teams[0][1]) << "\n\t2) " << Goti::getColorName(teams[1][0]) << " and " << Goti::getColorName(teams[1][1]) << "\nEnter any key to continue: ";
    cin.ignore();
    getline(cin, temp);
}
void Team::verifyKill()
{
    // through each color
    for (int i = 0; i < 4; i++)
    {
        // checking which team, player belong to
        for (int k = 0; k < 2; k++)
        {
            for (int m = 0; m < 2; m++)
            {
                if (turn == teams[k][m])
                {
                    team_turn = k;
                }
            }
        }
        // the current player can't kill himself and his fellow membor
        if (i == teams[team_turn][0] || i == teams[team_turn][1])
            continue;

        // through each goti of the color
        for (int j = 0; j < 4; j++)
        {
            // check if both position equal
            if (*Goti::gotis[turn][choice] == *Goti::gotis[i][j])
            {
                // if in safe location
                if (Goti::gotis[i][j]->isSafe())
                    continue;
                Goti::gotis[i][j]->returnHome();
                // if any team has >1 of it's gotis at the same place, it will kill them both.
                // it's a feature :p
            }
        }
    }
}

bool Team::isFinished() {
    // check if any membor of a team has all of it's gotis passed
    // from verify kill, we already have the team_turn
    for (int m = 0; m < 2; m++) {
        if (
            Goti::gotis[teams[team_turn][m]][0]->isPassed() &&
            Goti::gotis[teams[team_turn][m]][1]->isPassed() &&
            Goti::gotis[teams[team_turn][m]][2]->isPassed() &&
            Goti::gotis[teams[team_turn][m]][3]->isPassed()
        ) {
            cout << "\n\tTeam " << team_turn + 1 << " won having membors: " << Goti::getColorName(teams[team_turn][0]) << " and " << Goti::getColorName(teams[team_turn][1]) << endl;
            return true;
        }
    }
    return false;
}