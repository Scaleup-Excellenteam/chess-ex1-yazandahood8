#pragma once

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite, int row = -1, int col = -1) : Piece(isWhite, row, col) {}
    ~Bishop() {}

    bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;

private:
    char getPiece() const override { return isWhite ? 'B' : 'b'; }
};
