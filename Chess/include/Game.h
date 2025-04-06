#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"

class Game {
private:
    Board board;
    bool whiteTurn;

public:
    Game(const std::string& boardStr);
    int tryMove(const std::string& from, const std::string& to);
};

#endif
