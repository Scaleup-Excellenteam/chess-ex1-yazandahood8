#ifndef MOVE_RECOMMENDER_H
#define MOVE_RECOMMENDER_H

#include "Game.h"
#include "PriorityQueue.h"
#include "Move.h"
#include "MoveScorer.h"

class MoveRecommender {
public:
    static void recommendMoves(const Game& game, int depth);
};

#endif
