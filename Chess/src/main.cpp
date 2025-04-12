// main.cpp
#include "Chess.h"
#include "Game.h"
#include <sstream>

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
        res = a.getInput();
    }

    std::cout << std::endl << "Exiting " << std::endl;
    return 0;
}
