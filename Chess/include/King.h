#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}
    char getPiece() const override { return isWhite ? 'K' : 'k'; }
    bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;
};