#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}
    char getPiece() const override { return isWhite ? 'P' : 'p'; }
    bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;
};