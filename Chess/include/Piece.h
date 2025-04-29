#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece {
protected:
    bool isWhite;

public:
    Piece(bool isWhite);
    virtual ~Piece() = default;

    bool isWhitePiece() const { return isWhite; }

    virtual bool is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) = 0;
    virtual char get_type() = 0;
};

#endif // PIECE_H
