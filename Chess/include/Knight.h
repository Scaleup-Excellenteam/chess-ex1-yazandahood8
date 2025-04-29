#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}
    char getSymbol() const override { return isWhite ? 'N' : 'n'; }

    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const override {
        int dxAbs = std::abs(sx - dx), dyAbs = std::abs(sy - dy);
        return (dxAbs == 2 && dyAbs == 1) || (dxAbs == 1 && dyAbs == 2);
    }
};

#endif
