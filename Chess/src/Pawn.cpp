// In Pawn.cpp
#include "Pawn.h"
#include <cmath>
#include <iostream>
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Exceptions.h"

// Checks if a pawn move is legal (standard chess, excluding en passant).
// Handles forward movement (1 or 2 squares), captures, and starting rank logic.
// Parameters:
//   RowSource, ColSource          - starting square (0-7)
//   RowDestination, ColDestination- target square (0-7)
//   board                     - current board state
// Returns:
//   true if the move is legal for a pawn; false otherwise
bool Pawn::CheckLegalMove(int RowSource, int ColSource, int RowDestination, int ColDestination, Piece *board[8][8])
{
    int d;   // Direction the pawn moves (white: -1, black: +1)
    int row; // Row where pawn starts (white: 6, black: 1)

    if (isWhite)
    { // White pawns move "up" (decreasing row)
        d = -1;
        row = 6;
    }
    else
    { // Black pawns move "down" (increasing row)
        d = 1;
        row = 1;
    }
    // Capture: move diagonally by one square, must take opponent's piece
    int x=std::abs(ColDestination - ColSource);
    if (x == 1 && RowDestination == RowSource + d)
    {
        if (board[RowDestination][ColDestination] != nullptr &&
            board[RowDestination][ColDestination]->getColor() != this->isWhite)
        {
            return true;
        }
    }

    // Normal forward move (1 square), only if destination is empty
    if (ColSource == ColDestination)
    {
        if (RowDestination == RowSource + d && board[RowDestination][ColDestination] == nullptr)
        {
            return true;
        }
        // Two-square move from starting position, both squares must be empty
        if (RowSource == row && RowDestination == RowSource + 2 * d)
            if (board[RowSource + d][ColDestination] == nullptr &&
                board[RowDestination][ColDestination] == nullptr)
            {
                return true;
            }
    }

    return false;
}

// Promotes a pawn to the specified piece type (Queen, Rook, Bishop, or Knight).
// Throws IllegalException if the requested piece is invalid.
Piece *Pawn::Update(char UpdateTo, bool color)
{
    if (UpdateTo == 'Q' || UpdateTo == 'q')
    {
        return new Queen(color);
    }
    else if (UpdateTo == 'R' || UpdateTo == 'r')
    {
        return new Rook(color);
    }
    else if (UpdateTo == 'B' || UpdateTo == 'b')
    {
        return new Bishop(color);
    }
    else if (UpdateTo == 'N' || UpdateTo == 'n')
    {
        return new Knight(color);
    }
    else
    {
        throw IllegalException("Invalid promotion piece.");
    }
}
