#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
private:
    char type;

public:
    Rook(char t, bool isWhite) : Piece(isWhite) {
        type = t;
    }

    bool is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) override;

    char get_type() override;
};

#endif // ROOK_H
