#include "Bishop.h"

bool Bishop::is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) {
    int fromCol = input[0] - 'a';
    int fromRow = 8 - (input[1] - '0');
    int toCol = input[2] - 'a';
    int toRow = 8 - (input[3] - '0');

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Bishop moves diagonally
    if (abs(rowDiff) != abs(colDiff)) {
        return false;
    }

    int rowStep = (rowDiff > 0) ? 1 : -1;
    int colStep = (colDiff > 0) ? 1 : -1;

    int r = fromRow + rowStep;
    int c = fromCol + colStep;

    // Check if path is clear
    while (r != toRow && c != toCol) {
        if (board[r * 8 + c] != '#') {
            return false;
        }
        r += rowStep;
        c += colStep;
    }

    char targetPiece = board[toRow * 8 + toCol];
    
    if (targetPiece == '#') {
        return true;
    }

    if (isWhiteTurn && isupper(targetPiece)) {
        return false;
    }

    if (!isWhiteTurn && islower(targetPiece)) {
        return false;
    }

    return true;
}

char Bishop::get_type() {
    return type;
}
