#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}
    char getPiece() const override { return isWhite ? 'B' : 'b'; }
    bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;
};