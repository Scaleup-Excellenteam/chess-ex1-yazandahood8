#include "MoveScorer.h"
#include <cmath>

int MoveScorer::evaluate(int sx, int sy, int dx, int dy, const Board& board, bool whiteTurn) {
    Piece* moving = board.get(sx, sy);
    Piece* target = board.get(dx, dy);
    int score = 0;

    if (target && target->isWhitePiece() != whiteTurn)
        score += pieceValue(target);

    // בונוס אם מאיים על כלי חזק יותר
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            Piece* enemy = board.get(i, j);
            if (enemy && enemy->isWhitePiece() != whiteTurn &&
                moving->isValidMove(dx, dy, i, j, board))
                score += pieceValue(enemy) / 2;
        }

    // אם זז למשבצת חשופה
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            Piece* enemy = board.get(i, j);
            if (enemy && enemy->isWhitePiece() != whiteTurn &&
                enemy->isValidMove(i, j, dx, dy, board))
                score -= pieceValue(moving) / 2;
        }

    // בונוס לשליטה באמצע
    score += centralControl(dx, dy);

    // בונוס לפי שליטה יחסית על משבצות
    score += coverageDiff(board, whiteTurn);

    return score;
}

int MoveScorer::pieceValue(const Piece* p) {
    char symbol = tolower(p->getSymbol());
    switch (symbol) {
        case 'p': return 1;
        case 'n': return 3;
        case 'r': return 5;
        case 'k': return 1000;
    }
    return 0;
}

int MoveScorer::centralControl(int x, int y) {
    return (x >= 2 && x <= 5 && y >= 2 && y <= 5) ? 2 : 0;
}

int MoveScorer::coverageDiff(const Board& board, bool whiteTurn) {
    int ourCoverage = 0, theirCoverage = 0;
    for (int sx = 0; sx < 8; ++sx) {
        for (int sy = 0; sy < 8; ++sy) {
            Piece* p = board.get(sx, sy);
            if (!p) continue;
            for (int dx = 0; dx < 8; ++dx)
                for (int dy = 0; dy < 8; ++dy)
                    if (p->isValidMove(sx, sy, dx, dy, board)) {
                        if (p->isWhitePiece() == whiteTurn)
                            ++ourCoverage;
                        else
                            ++theirCoverage;
                    }
        }
    }
    return ourCoverage - theirCoverage;
}
