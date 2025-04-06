#include "King.h"
#include "Board.h"
#include <cmath>

bool King::isValidMove(int sx, int sy, int dx, int dy, const Board& board) const {
    return std::abs(sx - dx) <= 1 && std::abs(sy - dy) <= 1;
}
