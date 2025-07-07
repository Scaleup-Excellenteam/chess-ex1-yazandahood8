#include "Knight.h"
#include <cmath>

// Checks if a knight move is legal.
// Knights move in an "L" shape: two squares in one direction, then one square perpendicular.
// Parameters:
//   RowSource, ColSource           - starting square (0-7)
//   RowDestination, ColDestination - target square (0-7)
//   boardMove                      - current board state (not needed for basic knight movement)
// Returns:
//   true if the move is a legal knight jump; false otherwise
bool Knight::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* /*boardMove*/[8][8]) {
    int rowDiff = std::abs(RowDestination - RowSource);
    int colDiff = std::abs(ColDestination - ColSource);
    // Legal knight move: "L" shape (2 by 1 or 1 by 2)
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}
