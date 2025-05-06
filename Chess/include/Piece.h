#pragma once

class Piece {
public:
    Piece(bool isWhite, int row = -1, int col = -1)
        : isWhite(isWhite), row(row), col(col) {}

    virtual ~Piece() {}

    bool getColor() const { return isWhite; }

    int getRow() const { return row; }
    int getCol() const { return col; }

    void setPosition(int r, int c) {
        row = r;
        col = c;
    }

    virtual bool isLegalMove(int destRow, int destCol, Piece* board[8][8]) = 0;

    virtual bool isLegalMove(int destRow, int destCol) { return false; }

    virtual char getPiece() const = 0;

protected:
    bool isWhite;
    int row;
    int col;
};
