#include "Knight.h"
#include <cmath>
#include <cctype>

bool Knight::is_legel_movement(const string &input, const string &board, bool isWhiteTurn) {
    int fromCol = input[0] - 'a';
    int fromRow = 8 - (input[1] - '0');
    int toCol = input[2] - 'a';
    int toRow = 8 - (input[3] - '0');

    int dx = abs(toCol - fromCol);
    int dy = abs(toRow - fromRow);

    // Knight moves in L-shape: 2 by 1 or 1 by 2
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
        return false;
    }

    char target = board[toRow * 8 + toCol];

    // Can move if square is empty or has enemy piece
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

char Knight::get_type() {
    return type;
}
