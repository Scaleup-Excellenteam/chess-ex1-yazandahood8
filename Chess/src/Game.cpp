#include "Game.h"
#include <cctype>

Game::Game(const std::string& boardStr) : board(boardStr), whiteTurn(true) {}

int Game::tryMove(const std::string& from, const std::string& to) {
    int sx = 8 - (from[1] - '0');
    int sy = from[0] - 'a';
    int dx = 8 - (to[1] - '0');
    int dy = to[0] - 'a';

    Piece* piece = board.get(sx, sy);
    if (!piece) return 11;
    if (piece->isWhitePiece() != whiteTurn) return 12;

    Piece* target = board.get(dx, dy);
    if (target && target->isWhitePiece() == whiteTurn) return 13;

    // צור את input בפורמט e2e4
    std::string moveStr = from + to;

    // המרת מצב הלוח למחרוזת (64 תווים)
    std::string boardStr;
    boardStr.reserve(64);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* p = board.get(i, j);
            boardStr += (p ? p->get_type() : '#');
        }
    }

    if (!piece->is_legel_movement(moveStr, boardStr, whiteTurn)) return 21;

    board.move(sx, sy, dx, dy);
    whiteTurn = !whiteTurn;
    return 42;
}
