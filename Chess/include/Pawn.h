#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite);
    char getSymbol() const override;
    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const override;
};

#endif
