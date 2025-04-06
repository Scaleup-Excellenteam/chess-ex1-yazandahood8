#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite) {}
    char getSymbol() const override { return isWhite ? 'K' : 'k'; }
    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const override;
};

#endif
