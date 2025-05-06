#include "ValidatGame.h"
#include "Board.h"
#include "Piece.h"
#include "Knight.h"

int validateMove(const std::string& move, std::string& board, bool turn) {
    int srcCol = move[0] - 'a'; // column (letter)
    int srcRow = move[1] - '1'; // row (number)
    int destCol = move[2] - 'a';
    int destRow = move[3] - '1';

    Board boardObj;
    boardObj.loadFromString(board);

    Piece* srcPiece = boardObj.boardMove[srcRow][srcCol].get();
    Piece* destPiece = boardObj.boardMove[destRow][destCol].get();

    if (!srcPiece)
        return 11; // No piece at source

    if (srcPiece->getColor() != turn)
        return 12; // Turn mismatch

    if (destPiece && destPiece->getColor() == srcPiece->getColor())
        return 13; // Can't capture own piece

    // Always pass 3 arguments: legal check needs the board
    Piece* const* const* rawBoard = boardObj.getRawBoard();
    if (!srcPiece->isLegalMove(destRow, destCol, (Piece* (*)[8])rawBoard))
        return 21; // Illegal move

    // Apply move
    srcPiece->setPosition(destRow, destCol);
    boardObj.boardMove[destRow][destCol] = std::move(boardObj.boardMove[srcRow][srcCol]);
    boardObj.boardMove[srcRow][srcCol] = nullptr;

    board = boardObj.getBoardString();
    return 42; // Success
}
