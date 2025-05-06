#include "Bishop.h"
#include <cmath>  

bool Bishop::isLegalMove(int destRow, int destCol, Piece* board[8][8]) {
    int srcRow = getRow();
    int srcCol = getCol();

    if (std::abs(destRow - srcRow) != std::abs(destCol - srcCol))
        return false;

    int rowOffset = (destRow > srcRow) ? 1 : -1;
    int colOffset = (destCol > srcCol) ? 1 : -1;

    int checkRow = srcRow + rowOffset;
    int checkCol = srcCol + colOffset;

    while (checkRow != destRow || checkCol != destCol) {
        if (board[checkRow][checkCol] != nullptr)
            return false;
        checkRow += rowOffset;
        checkCol += colOffset;
    }

    return true;
}
