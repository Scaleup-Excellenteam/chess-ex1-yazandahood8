#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "MoveValidator.h"

bool Queen::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    return MoveValidator::isStraightPathClear(srcRow, srcCol, destRow, destCol, board) ||
           MoveValidator::isDiagonalPathClear(srcRow, srcCol, destRow, destCol, board);
}

    return rookHelper.isLegalMove(srcRow, srcCol, destRow, destCol, boardMove) ||
           bishopHelper.isLegalMove(srcRow, srcCol, destRow, destCol, boardMove);
}
