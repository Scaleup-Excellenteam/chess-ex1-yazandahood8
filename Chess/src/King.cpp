#include "King.h"
#include <string>
#include <cmath>
#include <cctype>

bool King::is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) {
    int col_from = input[0] - 'a';
    int row_from = 8 - (input[1] - '0');
    int col_to = input[2] - 'a';
    int row_to = 8 - (input[3] - '0');
//
    int dx = std::abs(col_to - col_from);
    int dy = std::abs(row_to - row_from);

    // King moves only 1 square in any direction
    if (dx > 1 || dy > 1) return false;

    char dest = board[row_to * 8 + col_to];
    if (dest == '#') return true;
    if (isWhiteTurn && std::isupper(dest)) return false;
    if (!isWhiteTurn && std::islower(dest)) return false;
    return true;
}

char King::get_type() {
    return type;
}
