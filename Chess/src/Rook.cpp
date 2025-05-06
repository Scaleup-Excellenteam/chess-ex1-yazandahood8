#include "Rook.h"

bool Rook::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, Piece* boardMove[8][8]) {
    if (srcRow == destRow) {
        int colOffset = (destCol - srcCol > 0) ? 1 : -1;
        for (int checkCol = srcCol + colOffset; checkCol != destCol; checkCol += colOffset) {
            if (boardMove[srcRow][checkCol] != nullptr)
                return false;
        }
        return true;
    }
    if (destCol == srcCol) {
        int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
        for (int checkRow = srcRow + rowOffset; checkRow != destRow; checkRow += rowOffset) {
            if (boardMove[checkRow][srcCol] != nullptr)
                return false;
        }
        return true;
    }
    return false;
}

bool Rook::isLegalMove(int destRow, int destCol, Piece* board[8][8]) {
    return areSquaresLegal(row, col, destRow, destCol, board);
}
