#include "ludoBoard.h"

class Classic : public Board
{
public:
    Classic();
    void verifyKill() override;
    bool isFinished() override;
};

Classic::Classic(): Board()
{
    initPieces();
    initBoard();
    draw();
    cout << "Before proceeding, the game mode is classic which means free for all.\nThe game will end when each player have all of his gotis passed.\nEnter the number of players that will play the game (2, 3 or 4):";
    cin >> max_players;
    if (max_players < 2) max_players = 2;
    max_players %= 4; // can't exceed 4
}

void Classic::verifyKill()
{
    // through each color
    for (int i = 0; i < 4; i++)
    {
        if (turn == i)
            continue; // so that the goti don't suicide, lorem dolor ipsum
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
bool Classic::isFinished()
{
    // check if each of the piece has passed
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!Goti::gotis[i][j]->isPassed())
                return false;
        }
    }
    return true; // the real win is the friends we made along the way
}