#include "King.h"
#include <cmath>

bool King::isLegalMove(int destRow, int destCol, Piece* board[8][8]) {
    int rowDiff = std::abs(destRow - row);
    int colDiff = std::abs(destCol - col);
    return (rowDiff <= 1 && colDiff <= 1);
}
