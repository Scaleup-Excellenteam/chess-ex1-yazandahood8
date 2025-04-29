#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {
private:
    char type;

public:
    King(char t, bool isWhite) : Piece(isWhite) {
        type = t;
    }

    bool is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) override;

    char get_type() override;
};

#endif // KING_H
