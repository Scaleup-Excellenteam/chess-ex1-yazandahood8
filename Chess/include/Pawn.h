#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite) {}
    char getSymbol() const override { return isWhite ? 'P' : 'p'; }

    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const override {
        int direction = isWhite ? -1 : 1;
        int startRow = isWhite ? 6 : 1;

        // Simple move
        if (dy == sy && dx == sx + direction && board.get(dx, dy) == nullptr)
            return true;

        // First double move
        if (dy == sy && sx == startRow && dx == sx + 2 * direction && 
            board.get(sx + direction, sy) == nullptr && board.get(dx, dy) == nullptr)
            return true;

        // Capture
        if (std::abs(dy - sy) == 1 && dx == sx + direction) {
            Piece* target = board.get(dx, dy);
            return target && target->isWhitePiece() != isWhite;
        }

        return false;
    }
};

#endif
