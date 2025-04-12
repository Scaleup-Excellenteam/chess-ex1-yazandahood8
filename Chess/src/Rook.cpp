#include "Rook.h"
#include <string>
#include <cctype>
#include <cmath>

bool Rook::is_legel_movement(const std::string &input, const std::string &board, bool isWhiteTurn) {
    // היגיון לבדיקה אם תזוזה חוקית לרוק – תנועה אנכית או אופקית בלבד
    int col_from = input[0] - 'a';
    int row_from = 8 - (input[1] - '0');
    int col_to = input[2] - 'a';
    int row_to = 8 - (input[3] - '0');

    if (col_from != col_to && row_from != row_to) return false;

    int step_row = (row_to > row_from) ? 1 : (row_to < row_from ? -1 : 0);
    int step_col = (col_to > col_from) ? 1 : (col_to < col_from ? -1 : 0);

    int r = row_from + step_row;
    int c = col_from + step_col;

    while (r != row_to || c != col_to) {
        if (board[r * 8 + c] != '#') return false;
        r += step_row;
        c += step_col;
    }

    char dest = board[row_to * 8 + col_to];
    if (dest == '#') return true;
    if (isWhiteTurn && std::isupper(dest)) return false;
    if (!isWhiteTurn && std::islower(dest)) return false;
    return true;
}

char Rook::get_type() {
    return type;
}
