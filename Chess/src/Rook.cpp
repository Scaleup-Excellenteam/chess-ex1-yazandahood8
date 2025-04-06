#include "Rook.h"
#include "Board.h"

bool Rook::isValidMove(int sx, int sy, int dx, int dy, const Board& board) const {
    if (sx != dx && sy != dy) return false;
    return board.isPathClear(sx, sy, dx, dy);
}
