#include "Piece.h"

Piece::~Piece() = default;

bool Piece::isLegalMove(int destRow, int destCol) {
    return false;
}

void Piece::setPosition(int r, int c) {
    row = r;
    col = c;
}

int Piece::getRow() const {
    return row;
}

int Piece::getCol() const {
    return col;
}
