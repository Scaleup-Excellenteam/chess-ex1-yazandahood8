#pragma once
#include "Chess.h"
#include "Piece.h"

// King chess piece class: implements movement rules and board representation.
class King : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    King(bool isWhite) : Piece(isWhite) {}

    // Destructor (virtual via base class; no additional cleanup needed)
    ~King() override = default;

    // Checks if a move is legal for the King.
    // Parameters:
    //   (int) RowSource, ColSource   - starting position (0-7)
    //   (int) RowDestination, ColDestination - ending position (0-7)
    //   boardMove - current board state (8x8 array of Piece pointers)
    // Returns:
    //   true if the move is legal by chess rules; false otherwise
    bool CheckLegalMove(int, int, int, int, Piece* boardMove[8][8]) override;

    // Returns 'K' for white king, 'k' for black king (for display/printing)
    char getPiece() const override { return isWhite ? 'K' : 'k'; }
};
