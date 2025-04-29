#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite);
    char getSymbol() const override;
    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const override;
};

#endif
