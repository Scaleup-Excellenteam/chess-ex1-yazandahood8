#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "MoveValidator.h"

// Checks if a queen move is legal by delegating to both rook and bishop path checkers.
// The queen can move any number of squares in a straight line, horizontally, vertically, or diagonally.
// Returns true if the move follows either rook or bishop movement rules and the path is unobstructed.
bool Queen::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) {
    return MoveValidator::CheckRookPath(RowSource, ColSource, RowDestination, ColDestination, boardMove) ||
           MoveValidator::CheckBishopPath(RowSource, ColSource, RowDestination, ColDestination, boardMove);
}
