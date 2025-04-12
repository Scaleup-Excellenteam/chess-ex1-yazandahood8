#include "Piece.h"

Piece::Piece(bool isWhite) {
    this->isWhite = isWhite;
}

bool Piece::isWhitePiece() const {
    return isWhite;
}
