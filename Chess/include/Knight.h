#pragma once
#include "Piece.h"


class Knight : public Piece {
public:
    Knight(bool isWhite): Piece(isWhite) {}
    ~Knight() {}
	bool areSquaresLegal(int, int, int, int) override;
private:
    char getPiece() const override { return isWhite ? 'N' : 'n'; }


};

