#include "Pawn.h"
#include <cmath>

bool Pawn::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, Piece* boardMove[8][8]) {
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
        return false;

    int direction = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    if (srcCol == destCol) {
        // One step forward
        if (destRow == srcRow + direction && boardMove[destRow][destCol] == nullptr)
            return true;

        // First move: two steps forward
        if (srcRow == startRow &&
            destRow == srcRow + 2 * direction &&
            boardMove[srcRow + direction][srcCol] == nullptr &&
            boardMove[destRow][destCol] == nullptr)
            return true;
    }

    if (std::abs(destCol - srcCol) == 1 &&
        destRow == srcRow + direction &&
        boardMove[destRow][destCol] != nullptr &&
        boardMove[destRow][destCol]->getColor() != isWhite)
        return true;

    return false;
}
