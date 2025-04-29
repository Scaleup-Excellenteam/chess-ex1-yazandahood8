#include "Knight.h"
#include "Board.h"
#include <cmath>

Knight::Knight(bool isWhite) : Piece(isWhite) {}

char Knight::getSymbol() const {
    return isWhite ? 'N' : 'n';
}

bool Knight::isValidMove(int sx, int sy, int dx, int dy, const Board& board) const {
    int dxAbs = std::abs(sx - dx), dyAbs = std::abs(sy - dy);
    return (dxAbs == 2 && dyAbs == 1) || (dxAbs == 1 && dyAbs == 2);
}
