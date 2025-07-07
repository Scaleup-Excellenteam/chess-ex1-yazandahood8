#pragma once

#include "Piece.h"

// Rook chess piece class: implements movement rules for a rook.
class Rook : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    Rook(bool isWhite) : Piece(isWhite) {}

    // Destructor (virtual via base class; no special cleanup needed)
    ~Rook() override = default;

    // Checks if a move is legal for the rook (any number of squares along a row or column).
    // Parameters:
    //   (int) RowSource, ColSource           - starting position (0-7)
    //   (int) RowDestination, ColDestination - destination position (0-7)
    //   boardMove                            - current board state (8x8 array of Piece pointers)
    // Returns:
    //   true if the move is legal for a rook; false otherwise
    bool CheckLegalMove(int, int, int, int, Piece* boardMove[8][8]) override;

    // Returns 'R' for white rook, 'r' for black rook (for display/printing)
    char getPiece() const override { return isWhite ? 'R' : 'r'; }
};
