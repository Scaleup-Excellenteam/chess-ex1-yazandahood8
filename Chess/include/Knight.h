#pragma once
#include "Piece.h"

// Knight chess piece class: implements movement rules for the knight.
class Knight : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    Knight(bool isWhite) : Piece(isWhite) {}

    // Destructor (virtual via base class; no special cleanup needed)
    ~Knight() override = default;

    // Checks if a move is legal for the Knight.
    // Parameters:
    //   RowSource, ColSource          - starting position (0-7)
    //   RowDestination, ColDestination- ending position (0-7)
    //   boardMove                     - current board state (8x8 array of Piece pointers)
    // Returns:
    //   true if the move is legal for a knight; false otherwise
    bool CheckLegalMove(int, int, int, int, Piece* boardMove[8][8]) override;

    // Returns 'N' for white knight, 'n' for black knight (for display)
    char getPiece() const override { return isWhite ? 'N' : 'n'; }
};
