#include "Bishop.h"
#include "MoveValidator.h"

// Checks if a bishop move from (RowSource, ColSource) to (RowDestination, ColDestination) is legal.
// Delegates the path checking to MoveValidator::CheckBishopPath, which ensures the path is unobstructed
// and follows diagonal movement rules.
bool Bishop::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) {
    return MoveValidator::CheckBishopPath(RowSource, ColSource, RowDestination, ColDestination, boardMove);
}
