#ifndef PIECE_H
#define PIECE_H

class Board;

class Piece {
protected:
    bool isWhite;
public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() {}
    bool isWhitePiece() const { return isWhite; }
    virtual char getSymbol() const = 0;
    virtual bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) const = 0;
};

#endif
