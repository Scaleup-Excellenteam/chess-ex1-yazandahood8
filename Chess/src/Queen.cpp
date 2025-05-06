#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "ValidatMove.h"

bool Queen::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, Piece* boardMove[8][8]) {
    Rook rookHelper(isWhite, row, col);
    Bishop bishopHelper(isWhite, row, col);
    return rookHelper.isLegalMove(destRow, destCol, boardMove) ||
           bishopHelper.isLegalMove(destRow, destCol, boardMove);
}

    return rookHelper.isLegalMove(srcRow, srcCol, destRow, destCol, boardMove) ||
           bishopHelper.isLegalMove(srcRow, srcCol, destRow, destCol, boardMove);
}
