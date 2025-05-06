#pragma once
#include "Piece.h"


class Knight : public Piece {
public:
    Knight(bool isWhite): Piece(isWhite) {}
    ~Knight() {}
	bool isLegalMove(int destRow, int destCol) override;
private:
    char getPiece() const override { return isWhite ? 'N' : 'n'; }


};

