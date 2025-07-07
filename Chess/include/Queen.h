#pragma once

#include "Piece.h"

// Queen chess piece class: combines rook and bishop movement rules.
class Queen : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    Queen(bool isWhite) : Piece(isWhite) {}

    // Destructor (virtual via base class; no special cleanup needed)
    ~Queen() override = default;

    // Checks if a move is legal for the Queen (any number of squares along row, column, or diagonal).
    // Parameters:
    //   RowSource, ColSource          - starting position (0-7)
    //   RowDestination, ColDestination- destination position (0-7)
    //   boardMove                     - 8x8 array of Piece pointers representing the board
    // Returns:
    //   true if the move is legal for a queen; false otherwise
    bool CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) override;

    // Returns 'Q' for white queen, 'q' for black queen (for display/printing)
    char getPiece() const override { return isWhite ? 'Q' : 'q'; }
};
