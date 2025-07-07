#include "Rook.h"
#include "MoveValidator.h"

// Checks if a rook move is legal.
// A rook can move any number of squares horizontally or vertically, as long as the path is unobstructed.
// Delegates the path check to MoveValidator::CheckRookPath.
bool Rook::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) {
    return MoveValidator::CheckRookPath(RowSource, ColSource, RowDestination, ColDestination, boardMove);
}
