// main.cpp
#include "Chess.h"
#include "Game.h"
#include "MoveRecommender.h"
#include <sstream>
#include <iostream>

int main()
{
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(board);
    Game game(board);

    int codeResponse = 0;
    std::string res = a.getInput();

    while (res != "exit")
    {
        std::string from, to;
        std::stringstream ss(res);
        ss >> from >> to;

        codeResponse = game.tryMove(from, to);

        a.setCodeResponse(codeResponse);

        // כאן המלצת מהלכים לפני קבלת הקלט הבא
        if (codeResponse == 42 || codeResponse == 41) { // מהלך חוקי
            std::cout << "\nRecommended moves:\n";
            MoveRecommender::recommendMoves(game, 2); // עומק 2
        }

        res = a.getInput();
    }

    std::cout << "\nExiting...\n";
    return 0;
}
