#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}
    char getPiece() const override { return isWhite ? 'N' : 'n'; }
    bool isLegalMove(int destRow, int destCol) override;
};