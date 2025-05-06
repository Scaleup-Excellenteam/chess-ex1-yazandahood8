#include "ValidatGame.h"
#include "Board.h"
#include "Piece.h"
#include "Knight.h"

int validateMove(const std::string& move, std::string& board, bool turn) {
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    Board boardObj;
    boardObj.loadFromString(board);

    Piece* srcPiece = boardObj.boardMove[srcRow][srcCol];
    Piece* destPiece = boardObj.boardMove[destRow][destCol];

    // No piece at source
    if (!srcPiece)
        return 11;

    // Turn mismatch
    if (srcPiece->getColor() != turn)
        return 12;

    // Can't capture own piece
    if (destPiece && destPiece->getColor() == srcPiece->getColor())
        return 13;

    // Validate move legality
    if (dynamic_cast<Knight*>(srcPiece)) {
        if (!srcPiece->isLegalMove(destRow, destCol))
            return 21;
    } else {
        if (!srcPiece->isLegalMove(destRow, destCol, boardObj.boardMove))
            return 21;
    }

    // Apply move
    srcPiece->setPosition(destRow, destCol);
    boardObj.boardMove[destRow][destCol] = srcPiece;
    boardObj.boardMove[srcRow][srcCol] = nullptr;

    board = boardObj.getBoardString();
    return 42;
}
