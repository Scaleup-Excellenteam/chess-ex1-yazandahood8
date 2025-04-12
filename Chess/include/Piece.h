#ifndef PIECE_H
#define PIECE_H

#include <string>
using namespace std;

class Piece {
protected:
    bool isWhite;

public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() {}

    bool isWhitePiece() const { return isWhite; }

    virtual bool is_legel_movement(const string &input, const string &board, bool isWhiteTurn) = 0;
    virtual char get_type() = 0;
};

#endif // PIECE_H
