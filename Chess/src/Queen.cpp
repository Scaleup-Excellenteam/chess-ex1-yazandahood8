#include "Queen.h"

bool Queen::is_legel_movement(const string &input, const string &board, bool isWhiteTurn) {
    int fromCol = input[0] - 'a';
    int fromRow = 8 - (input[1] - '0');
    int toCol = input[2] - 'a';
    int toRow = 8 - (input[3] - '0');

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0 ? 1 : -1);
    int colStep = (colDiff == 0) ? 0 : (colDiff > 0 ? 1 : -1);

    // Queen can move straight or diagonal
    if (!(fromRow == toRow || fromCol == toCol || abs(rowDiff) == abs(colDiff))) {
        return false;
    }

    int r = fromRow + rowStep;
    int c = fromCol + colStep;

    // Check if path is clear
    while (r != toRow || c != toCol) {
        if (board[r * 8 + c] != '#') {
            return false;
        }
        r += rowStep;
        c += colStep;
    }

    char target = board[toRow * 8 + toCol];

    // Can move if square is empty or has opponent piece
    if (target == '#') {
        return true;
    }

    if (isWhiteTurn && isupper(target)) {
        return false;
    }

    if (!isWhiteTurn && islower(target)) {
        return false;
    }

    return true;
}

char Queen::get_type() {
    return type;
}
