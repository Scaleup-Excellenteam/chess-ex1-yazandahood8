#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

char Pawn::getSymbol() const {
    return isWhite ? 'P' : 'p';
}

bool Pawn::isValidMove(int sx, int sy, int dx, int dy, const Board& board) const {
    int direction = isWhite ? -1 : 1;
    int startRow = isWhite ? 6 : 1;

    // Simple forward move
    if (dy == sy && dx == sx + direction && board.get(dx, dy) == nullptr)
        return true;

    // First move: double forward
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
