#include "ValidatMove.h"
#include "Piece.h"
#include <cstdlib>
bool MoveValidator::isStraightPathClear(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if (srcRow == destRow) {
        int step = (destCol - srcCol > 0) ? 1 : -1;
        for (int c = srcCol + step; c != destCol; c += step) {
            if (board[srcRow][c]) return false;
        }
        return true;
    }
    if (srcCol == destCol) {
        int step = (destRow - srcRow > 0) ? 1 : -1;
        for (int r = srcRow + step; r != destRow; r += step) {
            if (board[r][srcCol]) return false;
        }
        return true;
    }
    return false;
}

bool MoveValidator::isDiagonalPathClear(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if (abs(destRow - srcRow) != abs(destCol - srcCol)) return false;

    int rowStep = (destRow - srcRow > 0) ? 1 : -1;
    int colStep = (destCol - srcCol > 0) ? 1 : -1;

    for (int r = srcRow + rowStep, c = srcCol + colStep; r != destRow; r += rowStep, c += colStep) {
        if (board[r][c]) return false;
    }
    return true;
}
