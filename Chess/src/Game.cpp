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

    if (!piece->isValidMove(sx, sy, dx, dy, board)) return 21;

    board.move(sx, sy, dx, dy);
    whiteTurn = !whiteTurn;
    return 42;
}
