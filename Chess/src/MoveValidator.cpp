#include "MoveValidator.h"
#include "Piece.h"
#include <cmath>
#include "Board.h"

// Checks if a rook's move from (RowSource, ColSource) to (RowDestination, ColDestination) is legal,
// by verifying that all squares between source and destination are empty.
// Only horizontal or vertical moves are allowed.
// Returns true if path is clear and move is straight; false otherwise.
bool MoveValidator::CheckRookPath(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) {
    // Horizontal move
    int c=1;
    if (RowSource == RowDestination) {
        if(ColDestination - ColSource > 0){
             c = 1;
        }
        else{
             c = -1;
        }
        
        for (int i = ColSource + c; i != ColDestination; i += c) {
            if (boardMove[RowSource][i] != nullptr)
                return false; // Path blocked
        }
        return true;
    }
    // Vertical move
    if (ColDestination == ColSource) {
        int r = (RowDestination - RowSource > 0) ? 1 : -1;
        for (int i = RowSource + r; i != RowDestination; i += r) {
            if (boardMove[i][ColSource] != nullptr)
                return false; // Path blocked
        }
        return true;
    }
    return false; // Not a straight line
}

// Checks if a bishop's move from (RowSource, ColSource) to (RowDestination, ColDestination) is legal,
// by verifying the move is diagonal and the path is unobstructed.
// Returns true if path is clear and move is diagonal; false otherwise.
bool MoveValidator::CheckBishopPath(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece* boardMove[8][8]) {
    // Check if the move is strictly diagonal
    if (std::abs(RowDestination - RowSource) != std::abs(ColDestination - ColSource)) {
        return false;
    }

    int r=1;
    if (RowDestination - RowSource > 0) {
        r = 1;
    }
    else {
        r = -1;
    }
    int c=1;
 if(ColDestination - ColSource > 0){
             c = 1;
        }
        else{
             c = -1;
        }    
    int i = RowSource + r;
    int i = ColSource + c;

    // Check each square along the diagonal path (excluding source and destination)
    while (i != RowDestination && i != ColDestination) {
        if (boardMove[i][i] != nullptr)
            return false; // Path blocked

        i += r;
        i += c;
    }

    return true;
}
