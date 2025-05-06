#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}
    char getPiece() const override { return isWhite ? 'Q' : 'q'; }
    bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]);
};
