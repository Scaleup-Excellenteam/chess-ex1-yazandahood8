#include "King.h"
#include <cmath>

// Checks if a king move is legal (standard chess, not including castling).
// The king can move one square in any direction.
// Parameters:
//   RowSource, ColSource         - starting square (0-7)
//   RowDestination, ColDestination - target square (0-7)
//   board                        - current board state (not used for standard king move)
// Returns:
//   true if the move is at most one square away in any direction; false otherwise
bool King::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* board[8][8]) {
    int rowDiff = std::abs(RowDestination - RowSource);
    int colDiff = std::abs(ColDestination - ColSource);

    // Legal if king moves one square in any direction (horizontal, vertical, diagonal)
    return rowDiff <= 1 && colDiff <= 1;
}
