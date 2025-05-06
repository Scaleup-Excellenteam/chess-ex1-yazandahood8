#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

bool Queen::areSquaresLegal(int /*srcRow*/, int /*srcCol*/, int destRow, int destCol, Piece* boardMove[8][8]) {
    Rook rookHelper(isWhite, row, col);
    Bishop bishopHelper(isWhite, row, col);
    return rookHelper.isLegalMove(destRow, destCol, boardMove) ||
           bishopHelper.isLegalMove(destRow, destCol, boardMove);
}

bool Queen::isLegalMove(int destRow, int destCol, Piece* boardMove[8][8]) {
    return areSquaresLegal(row, col, destRow, destCol, boardMove);
}
