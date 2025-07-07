#pragma once

class Piece;

// Utility class for checking chess piece move paths.
class MoveValidator {
public:
    // Checks if the path for a Bishop move is clear (no obstructions).
    // Parameters:
    //   RowSource, ColSource         - starting square (0-7)
    //   RowDestination, ColDestination - destination square (0-7)
    //   board                        - 8x8 array of Piece pointers representing the board
    // Returns:
    //   true if all squares between source and destination (diagonal path) are empty; false otherwise
    static bool CheckBishopPath(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* board[8][8]);

    // Checks if the path for a Rook move is clear (no obstructions).
    // Parameters:
    //   RowSource, ColSource         - starting square (0-7)
    //   RowDestination, ColDestination - destination square (0-7)
    //   board                        - 8x8 array of Piece pointers representing the board
    // Returns:
    //   true if all squares between source and destination (horizontal/vertical path) are empty; false otherwise
    static bool CheckRookPath(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* board[8][8]);
};
