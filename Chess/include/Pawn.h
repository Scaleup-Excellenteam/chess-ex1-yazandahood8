#pragma once
#include "Piece.h"

// Pawn chess piece class: implements movement and promotion for pawns.
class Pawn : public Piece {
public:
    // Constructor: sets the piece's color (true = white, false = black)
    Pawn(bool isWhite) : Piece(isWhite) {}

    // Destructor (virtual via base class; no special cleanup needed)
    ~Pawn() override = default;

    // Checks if a move is legal for the pawn, including normal moves, captures, and en passant.
    // Parameters:
    //   RowSource, ColSource         - starting position (0-7)
    //   RowDestination, ColDestination - destination position (0-7)
    //   boardMove                    - current board state (8x8 array of Piece pointers)
    // Returns:
    //   true if the move is legal for a pawn; false otherwise
    bool CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) override;

    // Returns 'P' for white pawn, 'p' for black pawn (for display/printing)
    char getPiece() const override { return isWhite ? 'P' : 'p'; }

    // Promotes a pawn to another piece type (Queen, Rook, Bishop, or Knight).
    // Parameters:
    //   UpdateTo - character representing the piece to promote to ('Q', 'R', 'B', 'N', etc.)
    //   color    - true for white, false for black
    // Returns:
    //   pointer to the new Piece instance (caller must manage the memory)
    static Piece* Update(char UpdateTo, bool color);
};
