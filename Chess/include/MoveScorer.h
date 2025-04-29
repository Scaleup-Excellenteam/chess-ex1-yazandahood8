#ifndef MOVE_SCORER_H
#define MOVE_SCORER_H

#include "Board.h"
#include "Piece.h"

class MoveScorer {
public:
    static int evaluate(int sx, int sy, int dx, int dy, const Board& board, bool whiteTurn);
    static int pieceValue(const Piece* p);
    static int centralControl(int x, int y);
    static int coverageDiff(const Board& board, bool whiteTurn);
};

#endif
