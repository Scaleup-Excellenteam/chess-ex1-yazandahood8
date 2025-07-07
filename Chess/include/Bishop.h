#pragma once

#include "Piece.h"

// The Bishop class models a chess bishop piece.
// Inherits from Piece and overrides legal move validation and symbol representation.
class Bishop : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    Bishop(bool isWhite) : Piece(isWhite) {}

    // Virtual destructor (good practice for base-class pointers)
    ~Bishop() override = default;

    // Determines if a bishop move is legal according to chess rules.
    // Bishops move any number of squares diagonally.
    // - RowSource, ColSource: starting position (0-7)
    // - RowDestination, ColDestination: target position (0-7)
    // - boardMove: current board, pointers to Piece or nullptr if empty
    // Returns true if the move is legal, false otherwise.
    bool CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) override;

    // Returns 'B' for white bishop, 'b' for black bishop (for display)
    char getPiece() const override { return isWhite ? 'B' : 'b'; }
};
