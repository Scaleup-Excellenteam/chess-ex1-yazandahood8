#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"
#include <string>

class Knight : public Piece {
private:
    char type;

public:
    Knight(char t, bool isWhite) : Piece(isWhite) {
        type = t;
    }

    bool is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) override;

    char get_type() override;
};

#endif // CHESS_KNIGHT_H
