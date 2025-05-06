#pragma once

#include "Piece.h"

class Rook: public Piece {
    public:
        Rook(bool isWhite): Piece(isWhite) {}
        ~Rook() {}
        bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) override;
    private:
        char getPiece() const override { return isWhite ? 'R' : 'r'; }

};
