#include "Piece.h"

Piece::Piece(bool isWhite) {
    this->isWhite = isWhite;
}

bool Piece::is_white() const {
    return isWhite;
}

// Default movement - should be overridden
bool Piece::is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) {
    return false;
}

char Piece::get_type() {
    return type;
}
