#include "Knight.h"
#include <cmath>

bool Knight::isLegalMove(int destRow, int destCol, Piece* /*board*/[8][8]) {
    int dRow = std::abs(destRow - row);
    int dCol = std::abs(destCol - col);
    return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
}
