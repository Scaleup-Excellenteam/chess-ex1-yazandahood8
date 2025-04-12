#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <string>
#include "Piece.h"

class Board {
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

public:
    Board(const std::string& initialState);
    Piece* get(int x, int y) const;
    void move(int sx, int sy, int dx, int dy);
    bool isPathClear(int sx, int sy, int dx, int dy) const;
};

#endif
