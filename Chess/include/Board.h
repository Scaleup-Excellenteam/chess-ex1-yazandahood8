#pragma once

#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <string>

// The Board class manages an 8x8 chess board and its pieces.
class Board {
public:
    Board();   // Constructor: initializes the board with pieces (default or empty)
    ~Board();  // Destructor: responsible for deleting dynamically allocated pieces

    // Loads the board layout from a string representation (e.g., FEN-like or custom)
    void loadFromString(const std::string& boardString);

    // Checks if a player of the given color can make a legal move
    // color: 'w' for white, 'b' for black
    bool canMove(char color);

    // 2D array holding pointers to the pieces on the board; nullptr means empty square
    Piece* boardMove[8][8];

    // Returns the current board state as a string (for saving or display)
    std::string getBoardString() const;

    // Disable copy constructor and copy assignment to prevent accidental copies
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
