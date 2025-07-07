#pragma once

using namespace std;

// Abstract base class for chess pieces.
// Provides interface and common properties for all specific piece types.
class Piece {
public:
    // Constructor: sets color (true = white, false = black)
    explicit Piece(bool isWhite) : isWhite(isWhite), row(-1), col(-1) {}

    // Constructor with initial position
    Piece(bool isWhite, int row, int col)
        : isWhite(isWhite), row(row), col(col) {}

    // Returns true if the piece is white, false if black
    bool getColor() const { return isWhite; }

    // Returns the current row of the piece (0-7)
    int getRow() const { return row; }
    // Returns the current column of the piece (0-7)
    int getCol() const { return col; }

    // Sets the current position of the piece
    void setPosition(int r, int c) {
        row = r;
        col = c;
    }

    // Pure virtual function: must be implemented by derived classes.
    // Checks if a move from (source row, col) to (destination row, col) is legal for this piece.
    // Parameters:
    //   boardMove - 8x8 array representing the current board state
    virtual bool CheckLegalMove(int, int, int, int, Piece* boardMove[8][8]) = 0;

    // Pure virtual function: returns character representing the piece for display.
    // (e.g., 'Q' for white queen, 'k' for black king)
    virtual char getPiece() const = 0;

    // Virtual destructor (ensures proper cleanup of derived classes)
    virtual ~Piece() {}

protected:
    bool isWhite; // true if piece is white, false if black
    int row, col; // piece position (row and column indices, 0-7)
};
