#include "MoveRecommender.h"
#include <iostream>

void MoveRecommender::recommendMoves(const Game& game, int depth) {
    PriorityQueue<Move, MoveComparator> queue;
    const Board& board = game.getBoard();
    bool whiteTurn = game.isWhiteTurn();

    for (int sx = 0; sx < 8; ++sx) {
        for (int sy = 0; sy < 8; ++sy) {
            Piece* p = board.get(sx, sy);
            if (!p || p->isWhitePiece() != whiteTurn) continue;

            for (int dx = 0; dx < 8; ++dx) {
                for (int dy = 0; dy < 8; ++dy) {
                    if (!p->isValidMove(sx, sy, dx, dy, board)) continue;

                    int score = MoveScorer::evaluate(sx, sy, dx, dy, board, whiteTurn);

                    std::string from = std::string(1, 'a' + sy) + std::to_string(8 - sx);
                    std::string to = std::string(1, 'a' + dy) + std::to_string(8 - dx);
                    queue.push(Move(from, to, score));
                }
            }
        }
    }

    std::cout << "Top 3 recommended moves:\n";
    int count = 0;
    for (const auto& move : queue) {
        std::cout << "- " << move.from << " -> " << move.to << " (score: " << move.score << ")\n";
        if (++count == 3) break;
    }
}
