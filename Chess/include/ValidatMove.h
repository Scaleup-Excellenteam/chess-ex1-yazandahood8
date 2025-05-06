#pragma once
#include "Piece.h"

class MoveValidator {
public:
    static bool isStraightPathClear(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]);
    static bool isDiagonalPathClear(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]);
};
